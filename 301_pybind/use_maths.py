

import numpy as np
import maths

A = np.array([[1., 2.],
              [3., 4.]], dtype=np.float64)
x = np.array([10., 20.], dtype=np.float64)
y = np.array([5., 6.], dtype=np.float64)

out = maths.Maths.LinAlg.axpy(A, x, y)
print(out)  # [ 55. 116.]

