#pragma once

#include <exception>

class FileIsNotBmpException : std::exception {};
class CorruptedFileException : std::exception {};
class FileCouldNotOpenException : std::exception {};
class DirectoryDoesNotExistException : std::exception {};
class WrongArgumentsException : std::exception {};
