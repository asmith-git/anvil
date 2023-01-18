//Copyright 2023 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "anvil/Console/Console.hpp"
#include <iostream>
#if ANVIL_OS == ANVIL_WINDOWS
	#include <Windows.h>
#endif

namespace anvil {
	// ConsoleText

	ConsoleText::ConsoleText() :
		foreground_colour(CONSOLE_WHITE),
		background_colour(CONSOLE_BLACK)
	{}

	ConsoleText::ConsoleText(const std::string& text) :
		ConsoleText(text, CONSOLE_WHITE)
	{}

	ConsoleText::ConsoleText(const std::string& text, const ConsoleColour foreground) :
		ConsoleText(text, foreground, CONSOLE_BLACK)
	{}

	ConsoleText::ConsoleText(const std::string& txt, const ConsoleColour foreground, const ConsoleColour background) :
		text(txt),
		foreground_colour(foreground),
		background_colour(background)
	{}

	// Console

	Console::Console() :
		_stdout_handle(INVALID_HANDLE_VALUE)
	{
		_state_stack.push_back(State());
#if ANVIL_OS == ANVIL_WINDOWS
		_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		DWORD mode = 0;
		GetConsoleMode(_stdout_handle, &mode);
		if((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != ENABLE_VIRTUAL_TERMINAL_PROCESSING) SetConsoleMode(_stdout_handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
	}

	Console::~Console() {

	}

	void Console::Print(ConsoleText text) {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		_state_stack.back().text.push_back(text);
		PrintNoState(text);
	}

	void Console::PrintNoState(ConsoleText text) {

#if ANVIL_OS == ANVIL_WINDOWS
		static ANVIL_CONSTEXPR_VAR const uint8_t g_forground_colours[] = {
			0,																			//CONSOLE_BLACK,
			FOREGROUND_INTENSITY,														//CONSOLE_GREY_DARK,
			FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,						//CONSOLE_GREY_LIGHT,
			FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY, //CONSOLE_WHITE,
			FOREGROUND_BLUE | FOREGROUND_INTENSITY,										//CONSOLE_BLUE_LIGHT
			FOREGROUND_GREEN | FOREGROUND_INTENSITY,									//CONSOLE_GREEN_LIGHT
			FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,					//CONSOLE_CYAN_LIGHT
			FOREGROUND_RED | FOREGROUND_INTENSITY,										//CONSOLE_RED_LIGHT
			FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,					//CONSOLE_MAGENTA_LIGHT
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,					//CONSOLE_YELLOW_LIGHT
			FOREGROUND_BLUE,															//CONSOLE_BLUE_DARK
			FOREGROUND_GREEN,															//CONSOLE_GREEN_DARK
			FOREGROUND_BLUE | FOREGROUND_GREEN,											//CONSOLE_CYAN_DARK
			FOREGROUND_RED,																//CONSOLE_RED_DARK
			FOREGROUND_RED | FOREGROUND_BLUE,											//CONSOLE_MAGENTA_DARK
			FOREGROUND_RED | FOREGROUND_GREEN,											//CONSOLE_YELLOW_DARK
		};

		static ANVIL_CONSTEXPR_VAR const uint8_t g_background_colours[] = {
			0,																			//CONSOLE_BLACK,
			BACKGROUND_INTENSITY,														//CONSOLE_GREY_DARK,
			BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,						//CONSOLE_GREY_LIGHT,
			BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY, //CONSOLE_WHITE,
			BACKGROUND_BLUE | BACKGROUND_INTENSITY,										//CONSOLE_BLUE_LIGHT
			BACKGROUND_GREEN | BACKGROUND_INTENSITY,									//CONSOLE_GREEN_LIGHT
			BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,					//CONSOLE_CYAN_LIGHT
			BACKGROUND_RED | BACKGROUND_INTENSITY,										//CONSOLE_RED_LIGHT
			BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,					//CONSOLE_MAGENTA_LIGHT
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,					//CONSOLE_YELLOW_LIGHT
			BACKGROUND_BLUE,															//CONSOLE_BLUE_DARK
			BACKGROUND_GREEN,															//CONSOLE_GREEN_DARK
			BACKGROUND_BLUE | BACKGROUND_GREEN,											//CONSOLE_CYAN_DARK
			BACKGROUND_RED,																//CONSOLE_RED_DARK
			BACKGROUND_RED | BACKGROUND_BLUE,											//CONSOLE_MAGENTA_DARK
			BACKGROUND_RED | BACKGROUND_GREEN,											//CONSOLE_YELLOW_DARK
		};

#if ANVIL_CPP_VER >= 2011
		enum { DEFAULT_CONSOLE = g_forground_colours[CONSOLE_WHITE] | g_background_colours[CONSOLE_BLACK] };
#else
		const WORD DEFAULT_CONSOLE = g_forground_colours[CONSOLE_WHITE] | g_background_colours[CONSOLE_BLACK];
#endif

		const WORD attribute = g_forground_colours[text.foreground_colour] | g_background_colours[text.background_colour];
		if(attribute != DEFAULT_CONSOLE) SetConsoleTextAttribute(_stdout_handle, attribute);
#endif

		std::cout.write(text.text.c_str(), text.text.size());

#if ANVIL_OS == ANVIL_WINDOWS
		if (attribute != DEFAULT_CONSOLE) SetConsoleTextAttribute(_stdout_handle, DEFAULT_CONSOLE);
#endif
	}

	void Console::Clear() {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		_state_stack.back().text.clear();

#if ANVIL_OS == ANVIL_WINDOWS
		PCWSTR tmp = L"\x1b[2J";
		WriteConsoleW(_stdout_handle, tmp, (DWORD)wcslen(tmp), NULL, NULL);
#endif
	}

	void Console::PushState() {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		_state_stack.push_back(State());
	}

	void Console::PopState() {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		_state_stack.pop_back();
		if (_state_stack.empty()) {
			_state_stack.push_back(State());
		}
		else {
			State tmp = std::move(_state_stack.back());
			LoadState(tmp);
		}
	}

	Console::State Console::SaveState() const {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		return _state_stack.back();
	}

	void Console::LoadState(const State& state) {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		Clear();
		_state_stack.back() = state;
		for (const ConsoleText& text : state.text) PrintNoState(text);
	}


	void Console::ProgressBar(float& percentage, ConsoleColour colour) {

		ConsoleColour bright_colour = colour;
		ConsoleColour dark_colour = colour;

		switch (colour) {
		case CONSOLE_BLACK:
			bright_colour = CONSOLE_GREY_DARK;
			dark_colour = CONSOLE_BLACK;
			break;
		case CONSOLE_GREY_DARK:
		case CONSOLE_GREY_LIGHT:
			bright_colour = CONSOLE_GREY_LIGHT;
			dark_colour = CONSOLE_GREY_DARK;
			break;
		case CONSOLE_WHITE:
			bright_colour = CONSOLE_WHITE;
			dark_colour = CONSOLE_GREY_LIGHT;
			break;
		case CONSOLE_BLUE_LIGHT:
		case CONSOLE_BLUE_DARK:
			bright_colour = CONSOLE_BLUE_LIGHT;
			dark_colour = CONSOLE_BLUE_DARK;
			break;
		case CONSOLE_GREEN_LIGHT:
		case CONSOLE_GREEN_DARK:
			bright_colour = CONSOLE_GREEN_LIGHT;
			dark_colour = CONSOLE_GREEN_DARK;
			break;
		case CONSOLE_CYAN_LIGHT:
		case CONSOLE_CYAN_DARK:
			bright_colour = CONSOLE_CYAN_LIGHT;
			dark_colour = CONSOLE_CYAN_DARK;
			break;
		case CONSOLE_RED_LIGHT:
		case CONSOLE_RED_DARK:
			bright_colour = CONSOLE_RED_LIGHT;
			dark_colour = CONSOLE_RED_DARK;
			break;
		case CONSOLE_MAGENTA_LIGHT:
		case CONSOLE_MAGENTA_DARK:
			bright_colour = CONSOLE_MAGENTA_LIGHT;
			dark_colour = CONSOLE_MAGENTA_DARK;
			break;
		case CONSOLE_YELLOW_LIGHT:
		case CONSOLE_YELLOW_DARK:
			bright_colour = CONSOLE_YELLOW_LIGHT;
			dark_colour = CONSOLE_YELLOW_DARK;
			break;
		}

		int32_t width = 80;
#if ANVIL_OS == ANVIL_WINDOWS
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(_stdout_handle, &csbi);
			width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			//height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		}
#endif
		State tmp = SaveState();

		ConsoleText bar1;
		ConsoleText bar2;
		bar1.foreground_colour = dark_colour;
		bar1.background_colour = bright_colour;
		bar2.foreground_colour = bright_colour;
		bar2.background_colour = dark_colour;

		while (percentage < 100.f) {
			LoadState(tmp);

			int32_t progress = static_cast<int32_t>(std::round(static_cast<float>(width) * (percentage / 100.f)));
			if (progress > width) progress = width;

			bar1.text.clear();
			bar2.text.clear();
			for (int32_t i = 0; i < progress; ++i) bar1.text += ' ';
			for (int32_t i = progress; i < width; ++i) bar2.text += ' ';

			const auto SetChar = [&bar1, &bar2](size_t i, char c)->void {
				size_t s = bar1.text.size();
				if (i < s) {
					bar1.text[i] = c;
				} else {
					i -= s;
					s = bar2.text.size();
					if (i < s) {
						bar2.text[i] = c;
					}
				}
			};

			const std::string msg = std::to_string(static_cast<int32_t>(std::round(percentage))) + "%";
			const size_t offset = (width / 2) - (msg.size() / 2);
			for (size_t i = 0; i < msg.size(); ++i) SetChar(offset + i, msg[i]);

			Print(bar1);
			Print(bar2);
			EndLine();
			
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

	std::string Console::InputString(const ConsoleText& prompt, const bool clear) {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		if (clear) {
			PushState();
			Clear();
		}
		Print(prompt);
		EndLine();
		Print(" > ");
		std::string tmp = InputString();
		if (clear) {
			PopState();
		} else {
			_state_stack.back().text.push_back(ConsoleText(tmp));
		}
		return tmp;
	}

	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<ConsoleText>& options, const bool clear) {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		if (options.size() <= 1u) return 0u;

		if (clear) {
			PushState();
			Clear();
		}

		std::string tmp;
		ConsoleText prompt2 = prompt;
		const size_t count = options.size();
		int32_t choice = 0;

		while (true) {
			Print(prompt);
			EndLine();
			for (size_t i = 0; i < count; ++i) {
				prompt2.text = "\t[" + std::to_string(i) + "]\t: " + options[i].text + '\n';
				Print(prompt2);
			}

			prompt2.text = "\nEnter a value between 0 and " + std::to_string(count - 1) + " :";
			tmp = InputString(prompt2, false);

			try {
				choice = std::stoi(tmp);
				if (choice >= 0 && choice < count) break;
			} catch (...) {

			}
			if(clear) Clear();
		}

		if (clear) PopState();

		return static_cast<size_t>(choice);
	}


	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const bool clear) {
		return InputChoice(prompt, options, CONSOLE_WHITE, clear);
	}

	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const bool clear) {
		return InputChoice(prompt, options, foreground, CONSOLE_BLACK, clear);
	}

	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const ConsoleColour background, const bool clear) {
		const size_t count = options.size();
		std::vector<ConsoleText> tmp(count);
		for (size_t i = 0u; i < count; ++i) {
			ConsoleText& ct = tmp[i];
			ct.foreground_colour = foreground;
			ct.background_colour = background;
			ct.text = options[i];
		}

		return InputChoice(prompt, tmp, clear);
	}

	size_t Console::InputChoice(const std::string& prompt, const std::vector<std::string>& options, const bool clear) {
		return InputChoice(ConsoleText(prompt), options, clear);
	}

	size_t Console::InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const bool clear) {
		return InputChoice(ConsoleText(prompt, foreground), options, foreground, clear);
	}

	size_t Console::InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const ConsoleColour background, const bool clear) {
		return InputChoice(ConsoleText(prompt, foreground, background), options, foreground, background, clear);
	}

	std::string Console::InputString() {
		enum { BUFFER_SIZE = 1024 };
		char buffer[BUFFER_SIZE];
		std::cin.getline(buffer, BUFFER_SIZE);
		return buffer;
	}
}