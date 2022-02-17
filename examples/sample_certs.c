/**
 * Copyright (c) 2021 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "azure_samples.h"

/* Paste in the your IoT Hub connection string  */
const char pico_az_connectionString[] = "[device connection string]";

const char pico_az_x509connectionString[] = "[device connection string]";

const char pico_az_x509certificate[] =
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_x509privatekey[] =
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";

const char pico_az_id_scope[] = "[ID Scope]";

const char pico_az_COMMON_NAME[] = "[custom-hsm-device]";

const char pico_az_CERTIFICATE[] = 
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_PRIVATE_KEY[] = 
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";

const char pico_az_securityTypeEnvironmentVariable[] = "connectionString"; // Input either 'connectionString' or 'DPS'

const char pico_az_connectionStringEnvironmentVariable[] = "[IOTHUB_DEVICE_CONNECTION_STRING]";

const char pico_az_dpsIdScopeEnvironmentVariable[] = "[IOTHUB_DEVICE_DPS_ID_SCOPE]";
