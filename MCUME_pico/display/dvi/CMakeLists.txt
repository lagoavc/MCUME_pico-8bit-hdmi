# Minimal CMakeLists for display/dvi (glue only)

# This directory contains only the dvi glue wrapper. The actual DVI implementation (PicoDVI) should be added by the user.

cmake_minimum_required(VERSION 3.12)
project(mcume_pico_dvi)

# If the real PicoDVI is added, its sources should be added in this subdir and HAVE_PICODVI defined.
