set(TARGET_NAME main)
set(TARGET_FILES    
    ${TARGET_NAME}.c
    sample_certs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/custom_hsm_example/custom_hsm_x509.c
    ${CMAKE_CURRENT_SOURCE_DIR}/iothub_ll_c2d_sample/iothub_ll_c2d_sample.c
    ${CMAKE_CURRENT_SOURCE_DIR}/iothub_ll_client_x509_sample/iothub_ll_client_x509_sample.c
    ${CMAKE_CURRENT_SOURCE_DIR}/iothub_ll_telemetry_sample/iothub_ll_telemetry_sample.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pnp/pnp_simple_thermostat/pnp_simple_thermostat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/prov_dev_client_ll_sample/prov_dev_client_ll_sample.c
    )

add_executable(${TARGET_NAME} ${TARGET_FILES})

target_sources(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/pnp/common/pnp_device_client_ll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/pnp/common/pnp_dps_ll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/pnp/common/pnp_protocol.c
        )

target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/pnp/common
        )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${TARGET_NAME} PRIVATE
        pico_stdlib
        hardware_spi
        ETHERNET_FILES
        SPI_FILES
        DHCP_FILES
        DNS_FILES
        TIMER_FILES
        AZURE_SDK_PORT_FILES
        mbedcrypto
        mbedx509
        mbedtls
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${TARGET_NAME})
