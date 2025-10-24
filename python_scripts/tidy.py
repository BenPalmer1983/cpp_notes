#!/usr/bin/env python3
"""
tidy.py

Formats C++ sources to a consistent style:

- Removes all single-line `using ...;`
- Places `{` and `}` on their own lines
- Collapses blank lines to at most one (EXCEPT exactly two between top-level functions)
- Keeps preprocessor lines intact
- Makes a .bak backup before overwriting the file

Usage:
  ./tidy.py path/to/File.cpp
  ./tidy.py path/to/Header.hpp
"""

import argparse
import re
import shutil
import sys
from pathlib import Path
from typing import List


class CppTidy:
    USING_LINE = re.compile(r'^[ \t]*using\b.*?;\s*$', re.MULTILINE)

    SIGLIKELY = re.compile(
        r'''^
            (?:[A-Za-z_][\w:<>~*&\s,]*\s+)?   # return type (very loose)
            [A-Za-z_][\w:<>~]*                # name
            \s*\([^;{}]*\)                    # parameter list (no semicolon/block)
            (\s*(?:noexcept|const|override|final))*\s*$   # qualifiers
        ''',
        re.VERBOSE,
    )

    def __init__(self) -> None:
        pass

    # ---------- public API ----------

    def process_text(self, code: str) -> str:
        code = self._remove_using_lines(code)
        code = self._split_braces_to_own_lines(code)
        lines = self._normalize_blank_lines(code)
        lines = self._enforce_two_blank_lines_between_functions(lines)
        return '\n'.join(lines) + '\n'

    def run_on_file(self, path: Path) -> None:
        if not path.exists() or not path.is_file():
            raise FileNotFoundError(f"No such file: {path}")

        original = path.read_text(encoding='utf-8', errors='replace')
        cleaned = self.process_text(original)

        # Backup
        backup = path.with_suffix(path.suffix + '.bak')
        shutil.copy2(path, backup)

        # Overwrite original (preserve mode)
        path.write_text(cleaned, encoding='utf-8')
        shutil.copymode(backup, path)

    # ---------- steps ----------

    def _remove_using_lines(self, code: str) -> str:
        return re.sub(self.USING_LINE, '', code)

    def _split_braces_to_own_lines(self, code: str) -> str:
        out_lines: List[str] = []

        for raw_line in code.splitlines():
            line = raw_line.rstrip('\n')

            # Preprocessor lines pass through unchanged
            if line.lstrip().startswith('#'):
                out_lines.append(line)
                continue

            buf: List[str] = []
            i = 0
            in_string = None

            def flush_segment():
                seg = ''.join(buf).rstrip()
                if seg != '':
                    out_lines.append(seg)
                else:
                    out_lines.append('')
                buf.clear()

            while i < len(line):
                ch = line[i]

                # Simple string / char literal tracking
                if in_string:
                    buf.append(ch)
                    if ch == in_string:
                        # unescaped?
                        backslashes = 0
                        j = i - 1
                        while j >= 0 and line[j] == '\\':
                            backslashes += 1
                            j -= 1
                        if backslashes % 2 == 0:
                            in_string = None
                    i += 1
                    continue
                else:
                    if ch in ('"', "'"):
                        in_string = ch
                        buf.append(ch)
                        i += 1
                        continue

                if ch in '{}':
                    pre = ''.join(buf).rstrip()
                    if pre:
                        out_lines.append(pre)
                    buf.clear()
                    out_lines.append(ch)  # brace on its own line
                    i += 1
                    # skip immediate spaces after a brace on same line
                    while i < len(line) and line[i] == ' ':
                        i += 1
                    continue

                buf.append(ch)
                i += 1

            tail = ''.join(buf).rstrip()
            if tail != '':
                out_lines.append(tail)
            else:
                out_lines.append('')

        return '\n'.join(out_lines)

    def _normalize_blank_lines(self, code: str) -> List[str]:
        lines = code.splitlines()
        result: List[str] = []
        blank_streak = 0
        for ln in lines:
            if ln.strip() == '':
                blank_streak += 1
                if blank_streak <= 1:
                    result.append('')
            else:
                blank_streak = 0
                result.append(ln.rstrip())

        while result and result[0].strip() == '':
            result.pop(0)
        while result and result[-1].strip() == '':
            result.pop()
        return result

    def _enforce_two_blank_lines_between_functions(self, lines: List[str]) -> List[str]:
        out: List[str] = []
        depth = 0
        pending_fn = False
        last_sig_looks_like_fn = False

        def previous_significant_line() -> str:
            for s in reversed(out):
                st = s.strip()
                if st and st not in {'{', '}'} and not s.lstrip().startswith('#'):
                    return s
            return ''

        i = 0
        while i < len(lines):
            ln = lines[i]
            st = ln.strip()

            if st == '{' and depth == 0:
                last_sig_looks_like_fn = bool(self.SIGLIKELY.match(previous_significant_line()))

            if st == '{':
                depth += 1
                if depth == 1 and last_sig_looks_like_fn:
                    pending_fn = True
                out.append(ln)
                i += 1
                continue

            if st == '}':
                out.append(ln)
                if depth == 1 and pending_fn:
                    # ensure exactly two blanks after a top-level function body
                    out.append('')
                    out.append('')
                    pending_fn = False
                    last_sig_looks_like_fn = False
                depth = max(0, depth - 1)
                i += 1
                continue

            out.append(ln)
            i += 1

        # Reduce any blank run >=3 to 2 (without touching our intended doubles)
        final: List[str] = []
        blank_run = 0
        for ln in out:
            if ln.strip() == '':
                blank_run += 1
                if blank_run <= 2:
                    final.append('')
            else:
                blank_run = 0
                final.append(ln)

        while final and final[0].strip() == '':
            final.pop(0)
        while final and final[-1].strip() == '':
            final.pop()

        return final


def _parse_args(argv: List[str]) -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Tidy C++ files in-place with a consistent style.")
    p.add_argument('path', metavar='FILE', help='Path to .cpp/.hpp file')
    return p.parse_args(argv)


def main(argv: List[str] = None) -> int:
    args = _parse_args(sys.argv[1:] if argv is None else argv)
    path = Path(args.path)

    try:
        CppTidy().run_on_file(path)
    except FileNotFoundError as e:
        print(str(e), file=sys.stderr)
        return 2
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1

    print(f"Backed up to: {path.with_suffix(path.suffix + '.bak')}")
    print(f"Wrote cleaned code to: {path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
