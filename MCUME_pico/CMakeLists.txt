*** Begin Patch
*** Update File: MCUME_pico/CMakeLists.txt
@@
-set(TARGET testkeymax)
+# Default small test target
+set(TARGET picospeccy_ili9341_usbhost)
@@
-include_directories(display)
+include_directories(display)
+include_directories(input)
@@
-set(DISPLAY_SOURCES 
-        display/pico_dsp.cpp
-        display/vga.cpp
-        display/vga_vmode.cpp
-        display/emuapi.cpp
-        display/AudioPlaySystem.cpp		
-    )
+## Display sources - use ILI9341/TFT path (avoid VGA/picovga for this target)
+set(DISPLAY_SOURCES 
+        display/pico_dsp.cpp
+        display/emuapi.cpp
+        display/AudioPlaySystem.cpp		
+    )
+
+# Input sources (GPIO gamepad + TinyUSB host HID)
+set(INPUT_SOURCES
+        input/gamepad_gpio.c
+        input/usb_host_hid.c
+)
@@
-add_executable(${TARGET}
-        ${PICO20_SOURCES}
-        ${PICO64_SOURCES}
-        ${PICO81_SOURCES}
-        ${PICO800_SOURCES}
-        ${PICO5200_SOURCES}
-        ${PICO8086_SOURCES}
-        ${PICOCOLEM_SOURCES}
-        ${PICOO2EM_SOURCES}
-        ${PICOVCS_SOURCES}
-        ${PICOSPECCY_SOURCES}
-        ${PICONOFRENDO_SOURCES}
-        ${TESTIO_SOURCES}
-        ${TESTVGA_SOURCES}
-        ${TESTKEYMAX_SOURCES}
-#        ${GFXENGINE_SOURCES}
-#        ${PICOSND_SOURCES}
-#        ${TESTPSRAM_SOURCES}
-#        ${PICOVALIDATION_SOURCES}
-#        ${PSRAM_SOURCES}
-#        ${VGA_T4_SOURCES}
-#        ${PICOVGA_T4_SOURCES}
-#        ${TFT_T_SOURCES}
-        ${DISPLAY_SOURCES}
-    )
+add_executable(${TARGET}
+        ${PICOSPECCY_SOURCES}
+        ${DISPLAY_SOURCES}
+        ${INPUT_SOURCES}
+    )
@@
-pico_generate_pio_header(${TARGET} ${CMAKE_CURRENT_LIST_DIR}/display/picovga.pio)
+pico_generate_pio_header(${TARGET} ${CMAKE_CURRENT_LIST_DIR}/display/picovga.pio)
@@
-target_link_libraries(${TARGET} pico_multicore
-        pico_stdlib
-        FatFs_SPI
-#        pico_scanvideo_dpi
-        hardware_adc
-        hardware_pio
-        hardware_pwm        
-    )
+target_link_libraries(${TARGET} pico_multicore
+        pico_stdlib
+        FatFs_SPI
+        hardware_adc
+        hardware_pio
+        hardware_pwm    
+        hardware_spi
+    )
+
+# If TinyUSB host is enabled, the necessary include paths and link directives
+# should be added by the user or via a system-provided tinyusb/pico-extras setup.
+option(USE_TINYUSB_HOST "Enable TinyUSB host HID integration" ON)
+if(USE_TINYUSB_HOST)
+    add_compile_definitions(USE_TINYUSB_HOST)
+    message(STATUS "TinyUSB host integration enabled - make sure tinyusb sources are available in the SDK externals or submodule")
+endif()
*** End Patch
