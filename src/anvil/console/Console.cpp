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

	static std::recursive_mutex g_console_mutex;

#if ANVIL_OS == ANVIL_WINDOWS

	static ANVIL_CONSTEXPR_FN WORD ConvertToWindowsColour(const ConsoleColour foreground, const ConsoleColour background) {
		WORD fore = 0u;
		WORD back = 0u;

		fore |= foreground & detail::CONSOLE_BLUE ? FOREGROUND_BLUE : 0u;
		back |= background & detail::CONSOLE_BLUE ? BACKGROUND_BLUE : 0u;
		fore |= foreground & detail::CONSOLE_GREEN ? FOREGROUND_GREEN : 0u;
		back |= background & detail::CONSOLE_GREEN ? BACKGROUND_GREEN : 0u;
		fore |= foreground & detail::CONSOLE_RED ? FOREGROUND_RED : 0u;
		back |= background & detail::CONSOLE_RED ? BACKGROUND_RED : 0u;
		fore |= foreground & detail::CONSOLE_LIGHT ? FOREGROUND_INTENSITY : 0u;
		back |= background & detail::CONSOLE_LIGHT ? BACKGROUND_INTENSITY : 0u;

		return fore | back;
	}

#if ANVIL_CPP_VER >= 2011
	enum { DEFAULT_CONSOLE = ConvertToWindowsColour(CONSOLE_WHITE, CONSOLE_BLACK) };
#else
	static const WORD DEFAULT_CONSOLE = ConvertToWindowsColour(CONSOLE_WHITE, CONSOLE_BLACK);
#endif
#endif

	// ConsoleText

	ConsoleText::ConsoleText() :
		_text(),
		_char(0),
		_foreground_colour(CONSOLE_WHITE),
		_background_colour(CONSOLE_BLACK),
		_is_char(0),
		_unused(0)
	{}

	ConsoleText::ConsoleText(const char c, const ConsoleColour foreground, const ConsoleColour background) :
		_text(),
		_char(static_cast<uint8_t>(c)),
		_foreground_colour(foreground),
		_background_colour(background),
		_is_char(1),
		_unused(0)
	{}

	ConsoleText::ConsoleText(const std::string& txt, const ConsoleColour foreground, const ConsoleColour background) :
		_text(txt),
		_char(0),
		_foreground_colour(foreground),
		_background_colour(background),
		_is_char(0),
		_unused(0)
	{}

	// Console

	Console::Console() {
		_state_stack.push_back(State());
#if ANVIL_OS == ANVIL_WINDOWS
		_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		DWORD mode = 0;
		GetConsoleMode(_stdout_handle, &mode);
		if((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != ENABLE_VIRTUAL_TERMINAL_PROCESSING) SetConsoleMode(_stdout_handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		_current_attribute = DEFAULT_CONSOLE;
#endif
	}

	Console::~Console() {

	}

	void Console::Print(const ConsoleText& text) {
		if (text._text.empty() && ! text._is_char) return;

		if (_state_lock == 0u) {
			std::lock_guard<std::recursive_mutex> lock(g_console_mutex);

			State& state = _state_stack.back();
			if (state.text.empty()) {
				state.text.push_back(text);

			}
			else {
				ConsoleText& prev = state.text.back();
				if (prev._foreground_colour == text._foreground_colour && prev._background_colour == text._background_colour) {
					if (text._is_char) prev._text += static_cast<char>(text._char);
					else prev._text += text._text;
				}
				else {
					state.text.push_back(text);
				}
			}
		}

		char c;
		const char* txt;
		size_t len;
		if (text._is_char) {
			c = static_cast<char>(text._char);
			txt = &c;
			len = 1u;
		} else {
			txt = text._text.c_str();
			len = text._text.size();
		}

#if ANVIL_OS == ANVIL_WINDOWS
		const WORD attribute = ConvertToWindowsColour(static_cast<ConsoleColour>(text._foreground_colour), static_cast<ConsoleColour>(text._background_colour));
		if (attribute != _current_attribute) {
			SetConsoleTextAttribute(_stdout_handle, attribute);
			_current_attribute = attribute;
		}

		WriteConsoleA(_stdout_handle, txt, static_cast<DWORD>(len), NULL, NULL);

#else
		std::cout.write(txt, len);
#endif
	}

	void Console::Clear() {
		enum { MAX_HEIGHT = 4096 };
		char buf[MAX_HEIGHT];
		auto s = GetSize();
		if (s.first > MAX_HEIGHT) s.first = MAX_HEIGHT;
		for (size_t i = 0; i < s.first; ++i) buf[i] = ' ';
		buf[s.first] = '\0';

		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		_state_stack.back().text.clear();

		LockState();
		if ANVIL_CONSTEXPR_FN (CURSOR_POSITION_SUPPORTED) SetCursorLocation({ 0,0 });
		for (size_t i = 0; i < s.second; ++i) Print(buf, CONSOLE_WHITE, CONSOLE_BLACK);
		if ANVIL_CONSTEXPR_FN(CURSOR_POSITION_SUPPORTED) SetCursorLocation({ 0,0 });
		UnlockState();
	}

	const Console::State& Console::PushState() {
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		_state_stack.push_back(State());
		return _state_stack[_state_stack.size() - 2u];
	}

	void Console::PopState() {
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		_state_stack.pop_back();
		if (_state_stack.empty()) {
			_state_stack.push_back(State());
		} else {
			State tmp = std::move(_state_stack.back());
			LoadState(tmp);
		}
	}

	Console::State Console::SaveState() const {
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		return _state_stack.back();
	}

	void Console::LoadState(const State& state) {
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		Clear();
		_state_stack.back() = state;
		LockState();
		for (const ConsoleText& text : state.text) Print(text);
		UnlockState();
	}

	std::pair<size_t, size_t> Console::GetSize() const {
		std::pair<size_t, size_t> tmp;
#if ANVIL_OS == ANVIL_WINDOWS
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(_stdout_handle, &csbi);
			tmp.first = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			tmp.second = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		}
#else
		tmp.first = 120;
		tmp.second = 80;
#endif
		return tmp;
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

		int32_t width = static_cast<int32_t>(GetWidth());

		ConsoleText bar1;
		ConsoleText bar2;
		bar1._foreground_colour = dark_colour;
		bar1._background_colour = bright_colour;
		bar2._foreground_colour = bright_colour;
		bar2._background_colour = dark_colour;

		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		State tmp;
		if ANVIL_CONSTEXPR_FN(!CURSOR_POSITION_SUPPORTED) tmp = SaveState();
		int32_t prev_progress = -1;
		std::pair<size_t, size_t> bar_location;
		if ANVIL_CONSTEXPR_FN (CURSOR_POSITION_SUPPORTED) bar_location = GetCursorLocation();

		LockState();
		while (percentage < 100.f) {

			int32_t progress = static_cast<int32_t>(std::round(static_cast<float>(width) * (percentage / 100.f)));
			if (progress > width) progress = width;

			if(progress != prev_progress) {
				if ANVIL_CONSTEXPR_FN(! CURSOR_POSITION_SUPPORTED) LoadState(tmp);
				bar1._text.clear();
				bar2._text.clear();
				for (int32_t i = 0; i < progress; ++i) bar1._text += ' ';
				for (int32_t i = progress; i < width; ++i) bar2._text += ' ';

				const auto SetChar = [&bar1, &bar2](size_t i, char c)->void {
					size_t s = bar1._text.size();
					if (i < s) {
						bar1._text[i] = c;
					} else {
						i -= s;
						s = bar2._text.size();
						if (i < s) {
							bar2._text[i] = c;
						}
					}
				};

				const std::string msg = std::to_string(static_cast<int32_t>(std::round(percentage))) + "%";
				const size_t offset = (width / 2) - (msg.size() / 2);
				for (size_t i = 0; i < msg.size(); ++i) SetChar(offset + i, msg[i]);

				if ANVIL_CONSTEXPR_FN(CURSOR_POSITION_SUPPORTED) {
					const auto prev_pos = GetCursorLocation();
					SetCursorLocation(bar_location);
					Print(bar1);
					Print(bar2);
					SetCursorLocation(prev_pos);
				} else {
					Print(bar1);
					Print(bar2);
					EndLine();
				}
			
				prev_progress = progress;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(66));
		}
		UnlockState();
	}

	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<ConsoleText>& options) {
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		if (options.size() <= 1u) return 0u;

		std::string tmp;
		ConsoleText prompt2 = prompt;
		const size_t count = options.size();
		int32_t choice = 0;

		Print(prompt);
		EndLine();
		for (size_t i = 0; i < count; ++i) {
			prompt2._text = "\t[" + std::to_string(i) + "]\t: ";
			if (options[i]._is_char) {
				prompt2._text += static_cast<char>(options[i]._char);
			} else {
				prompt2._text += options[i]._text;
			}
			prompt2._text += '\n';
			Print(prompt2);
		}

		std::pair<size_t, size_t> prev_location;
		if ANVIL_CONSTEXPR_FN(CURSOR_POSITION_SUPPORTED) prev_location = GetCursorLocation();

		while (true) {

			prompt2._text = "\nEnter a value between 0 and " + std::to_string(count - 1) + " :";
			Print(prompt2);
			tmp = InputString();

			try {
				choice = std::stoi(tmp);
				if (choice >= 0 && choice < count) break;
			} catch (...) {

			}

			Print("Invalid input, try again\n", CONSOLE_RED_LIGHT, static_cast<ConsoleColour>(prompt2._background_colour));

			if ANVIL_CONSTEXPR_FN(CURSOR_POSITION_SUPPORTED) SetCursorLocation(prev_location);
		}

		return static_cast<size_t>(choice);
	}

	size_t Console::InputChoice(const ConsoleText& prompt, const std::vector<std::string>& options) {
		const size_t count = options.size();
		std::vector<ConsoleText> tmp(count);
		for (size_t i = 0u; i < count; ++i) {
			ConsoleText& ct = tmp[i];
			ct._foreground_colour = prompt._foreground_colour;
			ct._background_colour = prompt._background_colour;
			ct._text = options[i];
		}

		return InputChoice(prompt, tmp);
	}

	size_t Console::InputChoice(const std::string& prompt, const std::vector<std::string>& options, const ConsoleColour foreground, const ConsoleColour background) {
		return InputChoice(ConsoleText(prompt, foreground, background), options);
	}

	bool Console::IsAtStartOfLine() const {
		//if (!_state_stack.back().text.empty()) {
		//	const std::string& tmp = _state_stack.back().text.back().text;
		//	if (!tmp.empty()) {
		//		if (tmp.back() != '\n') return true;
		//	}
		//}

		//return false;

		return GetCursorLocation().first == 0u;
	}

	std::string Console::InputString() {
		if(! IsAtStartOfLine()) EndLine();
		Print(" > ");

		std::string buffer;
		std::getline(std::cin, buffer);
		return buffer;
	}

	std::pair<size_t, size_t> Console::GetCursorLocation() const {
		std::pair<size_t, size_t> tmp(0u, 0u);

#if ANVIL_OS == ANVIL_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO info;
		memset(&info, 0, sizeof(info));
		GetConsoleScreenBufferInfo(_stdout_handle, &info);

		tmp.first = info.dwCursorPosition.X;
		tmp.second = info.dwCursorPosition.Y;
#else
		std::lock_guard<std::recursive_mutex> lock(g_console_mutex);
		const State& state = _state_stack.back();

		for (const ConsoleText& str : state.text) {
			for (char c : str.text) {
				if (c == '\n') {
					++tmp.second;
					tmp.first = 0u;
				} else {
					++tmp.first;
				}
			}
		}
#endif
		return tmp;
	}

	void Console::SetCursorLocation(size_t x, size_t y) {
#if ANVIL_OS == ANVIL_WINDOWS
		COORD pos;
		pos.X = static_cast<SHORT>(x);
		pos.Y = static_cast<SHORT>(y);
		SetConsoleCursorPosition(_stdout_handle, pos);
		
		//! \bug Current state will not be modified correctly if the console is written to
#endif
	}
}