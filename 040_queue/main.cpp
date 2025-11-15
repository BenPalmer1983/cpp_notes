#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <omp.h>



class Writer 
{
    
private:

    struct Item 
    {
        std::vector<double> data;
        std::string filename;
    };

    std::mutex _mutex;
    std::condition_variable _condition_variable;
    std::queue<Item> _queue_items;
    std::atomic<bool> _done;
    std::thread _worker_thread;

public:

    // Constructor
    Writer()
        : _done(false), _worker_thread([this]{ this->run(); }) {}

    // Non-copyable
    Writer(const Writer&) = delete;
    Writer& operator=(const Writer&) = delete;

    // Enqueue a dataset to write as CSV.
    // Takes ownership of `data` via move.
    void enqueue(std::vector<double>&& data, std::string filename) 
    {
        {
            std::lock_guard<std::mutex> lk(_mutex);
            _queue_items.push(Item{std::move(data), std::move(filename)});
        }
        _condition_variable.notify_one();
    }

    // Flush queue and stop the worker.
    void stop() {
        {
            std::lock_guard<std::mutex> lk(_mutex);
            _done = true;
        }
        _condition_variable.notify_one();
        if (_worker_thread.joinable()) _worker_thread.join();
    }

    ~Writer() { stop(); }

private:


    void run() 
    {
        for (;;) 
        {
            Item item;
            {
                std::unique_lock<std::mutex> lk(_mutex);
                _condition_variable.wait(lk, [this]{ return _done || !_queue_items.empty(); });
                if (_done && _queue_items.empty()) break;
                item = std::move(_queue_items.front());
                _queue_items.pop();
            }
            // Do file I/O outside the lock
            try {
                write_csv(item.filename, item.data);
            } catch (const std::exception& e) {
                std::cerr << "Writer error for '" << item.filename
                          << "': " << e.what() << "\n";
            }
        }
    }

public:

    static void write_csv(const std::string& filename,
                          const std::vector<double>& data)
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::ofstream ofs(filename, std::ios::out);
        if (!ofs) throw std::runtime_error("Failed to open file");

        // Writing the file (inner loop to simulate a larger file write)
        for (size_t i = 0; i < data.size(); i++) 
        {
            for(size_t j=0; j<20; j++)
            {
                ofs << data[i];
                if (i + 1 < data.size()) ofs << ',';
            }
        }
        ofs << '\n';
        ofs.flush();
        if (!ofs) throw std::runtime_error("Write failed");
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Write time: " << duration.count() << " ms\n";

    }
};


int main() 
{


    Writer writer;
    auto start = std::chrono::high_resolution_clock::now();

    // Simulate producing data in a loop
    for (int step = 0; step < 5; ++step) 
    {
        std::vector<double> data(10000);

        #pragma omp parallel for
        for (size_t i = 0; i < data.size(); i++)
        {
            double temp {};
            for (size_t j = 0; j < data.size(); j++)
            {
                temp = temp + data[j] / (j + 1);
            }
            data[i] += temp;
        }


        std::string fname = "output_" + std::to_string(step) + ".csv";
        std::cout << fname << std::endl;

        // Queue to write
        writer.enqueue(std::move(data), fname);

        // Write and wait
        //Writer::write_csv(fname, data);

        
    }

    writer.stop();
    std::cout << "All writes complete.\n";

    // Record end time
    auto end = std::chrono::high_resolution_clock::now();

    // Compute duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " ms\n";
}

