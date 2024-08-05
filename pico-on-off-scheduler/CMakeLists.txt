if (TARGET tinyusb_device)
        add_executable(pico-on-off-scheduler
                pico-on-off-scheduler.c
                )

        # pull in common dependencies
        target_link_libraries(pico-on-off-scheduler pico_stdlib)

        # enable usb output, disable uart output
        pico_enable_stdio_usb(hello_usb 1)
        pico_enable_stdio_uart(hello_usb 0)

        # create map/bin/hex file etc.
        pico_add_extra_outputs(pico-on-off-scheduler)

        # add url via pico_set_program_url
        example_auto_set_url(pico-on-off-scheduler)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building pico-on-off-scheduler because TinyUSB submodule is not initialized in the SDK")
endif()

