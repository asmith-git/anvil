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
		_state_stack.back().text.clear();

#if ANVIL_OS == ANVIL_WINDOWS
		PCWSTR tmp = L"\x1b[2J";
		WriteConsoleW(_stdout_handle, tmp, (DWORD)wcslen(tmp), NULL, NULL);
#endif
	}

	void Console::PushState() {
		_state_stack.push_back(State());
	}

	void Console::PopState() {
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
		return _state_stack.back();
	}

	void Console::LoadState(const State& state) {
		Clear();
		_state_stack.back() = state;
		for (const ConsoleText& text : state.text) PrintNoState(text);
	}

	std::string Console::InputString(const ConsoleText& prompt) {
		PushState();
		Clear();
		Print(prompt);
		EndLine();
		Print(" > ");
		std::string tmp = InputString();
		PopState();
		return tmp;
	}

	std::string Console::InputString() {
		enum { BUFFER_SIZE = 1024 };
		char buffer[BUFFER_SIZE];
		std::cin.getline(buffer, BUFFER_SIZE);
		return buffer;
	}
}