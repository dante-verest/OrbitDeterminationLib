// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#pragma warning(disable: 26495)
#include "Eigen/Dense"
#include <corecrt_math_defines.h>
//#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <array>
//#include <concepts>
//#include <stdexcept>
#include <cfloat>
#include <fstream>
#include <optional>
#include <memory>

#endif //PCH_H
