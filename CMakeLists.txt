cmake_minimum_required(VERSION 3.10)

# Proje adı
project(OtoparkYonetimSistemi)

# C++ Standartı (C++17 modern özellikler için iyidir)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tüm .cpp ve .h dosyalarını bul
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

# Uygulamayı oluştur
add_executable(OtoparkSistemi ${SOURCES} ${HEADERS})
