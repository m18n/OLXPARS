# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/move
    REF boost-1.79.0
    SHA512 1c62ca4673ca70dd1334ac6380f74db2f3827631d1419f658461bd4ab22a81406a2b1229adf48f92cf827a627e1997409c9911d8bc9ed6a5d5ac320127818fb0
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})
