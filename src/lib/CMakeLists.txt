add_library(
  draw SHARED
    # Loaders
    loaders/loader.cpp loaders/loader.h
    loaders/jpeg/jpeg.cpp loaders/jpeg/jpeg.h
    loaders/png/png.cpp loaders/png/png.h
    loaders/raw/raw.cpp loaders/raw/raw.h
    # Color
    color/color.cpp color/color.h
    color/rgb.h
    color/hsl.h
    color/hsv.h
    # Transforms
    transforms/transform.cpp transforms/transform.h
    # Adjustments
    adjustments/adjust.h adjustments/adjust.cpp
    adjustments/brightness.cpp adjustments/brightness.h
    adjustments/contrast.cpp adjustments/contrast.h
    adjustments/saturation.cpp adjustments/saturation.h
    adjustments/white-balance.cpp adjustments/white-balance.h
    adjustments/exposure.cpp adjustments/exposure.h
    adjustments/gamma.cpp adjustments/gamma.h
    adjustments/invert.cpp adjustments/invert.h
    adjustments/threshold.cpp adjustments/threshold.h
    adjustments/auto.cpp adjustments/auto.h
    # Filters
    filters/filter.cpp  filters/filter.h
    # filters/sharpen.cpp filters/sharpen.h
    filters/blur/gaussian.cpp filters/blur/gaussian.h
    filters/blur/box.cpp filters/blur/box.h
    # Drawing
    draw/draw.cpp draw/draw.h
    # core
    image.cpp image.h
    mask.h
)

target_link_libraries(
  draw
  PRIVATE
    jpeg
    png
    ${CMAKE_DL_LIBS}
)
