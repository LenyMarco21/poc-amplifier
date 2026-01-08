idf_component_register(SRCS "bt_app_av.c"
                            "bt_app_core.c"
                            "main.c"
                            "codec/tad5212.c"
                    PRIV_REQUIRES esp_driver_gpio esp_driver_i2s esp_driver_i2c bt nvs_flash esp_ringbuf esp_driver_dac
                    INCLUDE_DIRS ".")
