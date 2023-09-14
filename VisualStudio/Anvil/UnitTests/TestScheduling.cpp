#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 
#include "CppUnitTest.h"
#include "anvil/Scheduling.hpp"
#include <locale>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anvil { namespace scheduling {

	static float GetTimeMS() {
		static const uint64_t g_reference_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - g_reference_time) / 1000000.f;
	}

	class FixedTimeTask : public Task {
	private:
		volatile int _cpu_var;
	public:
		std::atomic_int* task_counter;
		float time_ms;
		bool use_cpu;

	protected:

		void OnExecution() final {
			float time_start = GetTimeMS();
			if (use_cpu) {
				while (GetTimeMS() <= (time_start + time_ms)) {
					_cpu_var += (int) std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
					_cpu_var += (int)std::sqrtf(_cpu_var + 1);
				}
			} else {
				std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(time_ms * 1000.f)));
			}

			if (task_counter) ++*task_counter;
		}

	public:

		FixedTimeTask() :
			_cpu_var(0),
			task_counter(nullptr),
			time_ms(0.f),
			use_cpu(true)
		{}

		virtual ~FixedTimeTask() {

		}
	};

	static ExampleSchedulerMultiThreaded g_scheduler(std::thread::hardware_concurrency());

	TEST_CLASS(TestScheduling)
	{
	public:


		void FixedTimeTest(float task_ms, bool use_cpu, float total_time) {
			size_t task_count = static_cast<size_t>(std::roundf(total_time / task_ms));

			float t1 = GetTimeMS();

			std::atomic_int task_counter = 0;

			try {

				FixedTimeTask* tasks = new FixedTimeTask[task_count];
				for (size_t i = 0u; i < task_count; ++i) {
					tasks[i].task_counter = &task_counter;
					tasks[i].time_ms = task_ms;
					tasks[i].use_cpu = use_cpu;
				}

				g_scheduler.Schedule(tasks, task_count);

				for (size_t i = 0u; i < task_count; ++i) tasks[i].Wait();

				delete[] tasks;

			} catch (std::exception& e) {
				Assert::Fail(std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>().from_bytes(e.what()).c_str());
			}

			float t2 = GetTimeMS();

			Assert::AreEqual((int)task_count, (int)task_counter, L"Number of tasks executed is wrong");

			float time_taken = t2 - t1;
			//float expected_time = total_time / static_cast<float>(std::thread::hardware_concurrency());
			float expected_time = total_time / static_cast<float>(std::thread::hardware_concurrency() + 1);

			Assert::IsTrue(time_taken >= (expected_time * 0.98f), (L"Finished faster than should be posible, took " + std::to_wstring(time_taken) + L"ms but minimum expected time is " + std::to_wstring(expected_time) + L"ms").c_str());

		}

		TEST_METHOD(FixedTask1_CPU_10Seconds) { 
			FixedTimeTest(1.f, true, 10000.f);
		}

		TEST_METHOD(FixedTask1_NoCPU_10Seconds) {
			FixedTimeTest(1.f, false, 10000.f);
		}

		TEST_METHOD(FixedTask1_CPU_1Minute) {
			FixedTimeTest(1.f, true, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask1_NoCPU_1Minute) {
			FixedTimeTest(1.f, false, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask1_CPU_10Minute) {
			FixedTimeTest(1.f, true, 1000.f * 60.f * 10.f);
		}
		
		TEST_METHOD(FixedTask1_NoCPU_10Minute) {
			FixedTimeTest(1.f, false, 1000.f * 60.f * 10.f);
		}

		TEST_METHOD(FixedTask10_CPU_10Seconds) {
			FixedTimeTest(10.f, true, 10000.f);
		}

		TEST_METHOD(FixedTask10_NoCPU_10Seconds) {
			FixedTimeTest(10.f, false, 10000.f);
		}

		TEST_METHOD(FixedTask10_CPU_1Minute) {
			FixedTimeTest(10.f, true, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask10_NoCPU_1Minute) {
			FixedTimeTest(10.f, false, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask10_CPU_10Minute) {
			FixedTimeTest(10.f, true, 1000.f * 60.f * 10.f);
		}
		
		TEST_METHOD(FixedTask10_NoCPU_10Minute) {
			FixedTimeTest(10.f, false, 1000.f * 60.f * 10.f);
		}

		TEST_METHOD(FixedTask100_CPU_10Seconds) {
			FixedTimeTest(100.f, true, 10000.f);
		}

		TEST_METHOD(FixedTask100_NoCPU_10Seconds) {
			FixedTimeTest(100.f, false, 10000.f);
		}

		TEST_METHOD(FixedTask100_CPU_1Minute) {
			FixedTimeTest(100.f, true, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask100_NoCPU_1Minute) {
			FixedTimeTest(100.f, false, 1000.f * 60.f);
		}

		TEST_METHOD(FixedTask100_CPU_10Minute) {
			FixedTimeTest(100.f, true, 1000.f * 60.f * 10.f);
		}
		
		TEST_METHOD(FixedTask100_NoCPU_10Minute) {
			FixedTimeTest(100.f, false, 1000.f * 60.f * 10.f);
		}

	};

}}
