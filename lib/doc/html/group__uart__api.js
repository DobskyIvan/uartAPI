var group__uart__api =
[
    [ "sUartApiFunctions", "structs_uart_api_functions.html", [
      [ "deinit", "structs_uart_api_functions.html#a9e80b0301f0f0be7c4d112a0aa18d359", null ],
      [ "setBaudrate", "structs_uart_api_functions.html#a565e3de903649073ad847c8d049adf84", null ],
      [ "setParity", "structs_uart_api_functions.html#a90b528da1f57508e7d6aa851112e934e", null ],
      [ "setStopBits", "structs_uart_api_functions.html#a43288cd18de364a0a5a7be40100f05c8", null ],
      [ "uartEnable", "structs_uart_api_functions.html#a4c4164b0beff5cee7170be1c10125264", null ],
      [ "uartGetByte", "structs_uart_api_functions.html#a9585b7c5d71071fd27624b0a47512e4c", null ],
      [ "uartPutByte", "structs_uart_api_functions.html#a05d7ef10359a39b5dd990a9a81faa36a", null ]
    ] ],
    [ "sUartApi", "structs_uart_api.html", [
      [ "config", "structs_uart_api.html#ac193df37dd067d5aa4c8d500647fb4df", null ],
      [ "functions", "structs_uart_api.html#a6de84a7699da8ee44120a7efd6ed7e33", null ],
      [ "state", "structs_uart_api.html#a2bb28db5749b4cafc6346826c42a1ca5", null ],
      [ "temp", "structs_uart_api.html#adbf2825f5c55ecc0d99395c6f19b7ef2", null ]
    ] ],
    [ "sUartApiConfig_", "structs_uart_api_config__.html", [
      [ "baudrate", "structs_uart_api_config__.html#ac4f06ea26ed6bd7ae83b92d64ac10b78", null ],
      [ "parity", "structs_uart_api_config__.html#a2baf56b056447a70b3e62b7d1afda371", null ],
      [ "ReceiveCB", "structs_uart_api_config__.html#af2a9c934946b6c525a6e43569da4b9fe", null ],
      [ "stopBits", "structs_uart_api_config__.html#a85177b7be3c98fad7a16ce46dc1d68f8", null ]
    ] ],
    [ "sUartApiState_", "structs_uart_api_state__.html", [
      [ "rxState", "structs_uart_api_state__.html#ae8050aa7ca046c8fe4a5daf5021c2a7f", null ],
      [ "txState", "structs_uart_api_state__.html#adca01ced4b57c9c94cf6b7b12a194b88", null ]
    ] ],
    [ "sUartApiTemp_", "structs_uart_api_temp__.html", [
      [ "receivedByte", "structs_uart_api_temp__.html#a7bef3d024d8387f41039ac89942ba68d", null ],
      [ "txDataLength", "structs_uart_api_temp__.html#a462c94c5357e1d79dae3528212ecd280", null ],
      [ "txDataPointer", "structs_uart_api_temp__.html#afb8fceaa1195695b9d3c31005e7e3afb", null ]
    ] ],
    [ "eErrorCode", "group__uart__api.html#gaae7d5b630c496f0cebd018d6d553dbed", [
      [ "E_NOERR", "group__uart__api.html#ggaae7d5b630c496f0cebd018d6d553dbedad651e84723f3769f0c5d5dff4e7cd11a", null ],
      [ "E_INITERR", "group__uart__api.html#ggaae7d5b630c496f0cebd018d6d553dbeda7e052a0633e19bbccb9c5d3692b061dd", null ],
      [ "E_COMMERR", "group__uart__api.html#ggaae7d5b630c496f0cebd018d6d553dbeda98792b5fd6b08aac36193f14a244a807", null ]
    ] ],
    [ "eParity", "group__uart__api.html#ga5dd41bdb6919f67fa9e52a00e289dfbe", [
      [ "PARITY_NONE", "group__uart__api.html#gga5dd41bdb6919f67fa9e52a00e289dfbea90674e2854f8cd4ce76ea0b4cd4546cc", null ],
      [ "PARITY_ODD", "group__uart__api.html#gga5dd41bdb6919f67fa9e52a00e289dfbea41443d13b163ffeaf59c4667472bc49c", null ],
      [ "PARITY_EVEN", "group__uart__api.html#gga5dd41bdb6919f67fa9e52a00e289dfbeae6172576b70fc73aefabd529c103c9b8", null ]
    ] ],
    [ "eRxState", "group__uart__api.html#gaf07405fec2fea0cf4bb6abdd6d305c96", [
      [ "STATE_RX_IDLE", "group__uart__api.html#ggaf07405fec2fea0cf4bb6abdd6d305c96a516714125b01eae93e5cb693fdc3a9e0", null ],
      [ "STATE_RX_ERROR", "group__uart__api.html#ggaf07405fec2fea0cf4bb6abdd6d305c96afbb71fcd5e10dfbcc33a8f5a00df1f95", null ],
      [ "STATE_RX_BUSY", "group__uart__api.html#ggaf07405fec2fea0cf4bb6abdd6d305c96afcb40c83d60cd2e7a99b361accec16d2", null ]
    ] ],
    [ "eRxSwitch", "group__uart__api.html#ga1065e42cc0c47617b7729af41eccee9c", [
      [ "STATE_RX_DISABLE", "group__uart__api.html#gga1065e42cc0c47617b7729af41eccee9caa5304c86cc1d114d349a23e5e84375f8", null ],
      [ "STATE_RX_ENABLE", "group__uart__api.html#gga1065e42cc0c47617b7729af41eccee9cab23c2a6f4d868371514256803801d6c7", null ]
    ] ],
    [ "eStopBits", "group__uart__api.html#ga2bcc74dcb5516a153e92e585f181adc8", [
      [ "STOP_BITS_0_5", "group__uart__api.html#gga2bcc74dcb5516a153e92e585f181adc8a3b8b3d301df730ca2c5c40c0db150f07", null ],
      [ "STOP_BITS_1", "group__uart__api.html#gga2bcc74dcb5516a153e92e585f181adc8ad5532387a525860bca665f556b235a61", null ],
      [ "STOP_BITS_1_5", "group__uart__api.html#gga2bcc74dcb5516a153e92e585f181adc8a577d4b33e6ebfc8ddf556ec0093ebcb5", null ],
      [ "STOP_BITS_2", "group__uart__api.html#gga2bcc74dcb5516a153e92e585f181adc8a47dc89ff50980f11f25190d3a05ed055", null ]
    ] ],
    [ "eTxState", "group__uart__api.html#gaf747a8e23b450e107ec3ab8ce02eb183", [
      [ "STATE_TX_IDLE", "group__uart__api.html#ggaf747a8e23b450e107ec3ab8ce02eb183ab1bd9fcf7cdb346f72d012adfca4767a", null ],
      [ "STATE_TX_ERROR", "group__uart__api.html#ggaf747a8e23b450e107ec3ab8ce02eb183a2f8f9098cf0d8208cdfaefedd6f7e9db", null ],
      [ "STATE_TX_BUSY", "group__uart__api.html#ggaf747a8e23b450e107ec3ab8ce02eb183a0697f8378734770e7f8f2eedc4a557a3", null ]
    ] ],
    [ "eTxSwitch", "group__uart__api.html#ga8df4129749fd06c0387eb173bbdc092e", [
      [ "STATE_TX_DISABLE", "group__uart__api.html#gga8df4129749fd06c0387eb173bbdc092eafe4a403b2c61994ee3515ef0ed1e84d3", null ],
      [ "STATE_TX_ENABLE", "group__uart__api.html#gga8df4129749fd06c0387eb173bbdc092ea0bbd9d77001838f9e624a8dc096d1317", null ]
    ] ],
    [ "CBByteReceivedIT", "group__uart__api.html#gafeb97a13c2d98d79a5de3cd4ea6a7158", null ],
    [ "CBTransmitterEmptyIT", "group__uart__api.html#ga1dbe19d4b3e7dae305be9702f5111215", null ],
    [ "uartDeinit", "group__uart__api.html#gaa835fe5ae290e68723e05746b8980510", null ],
    [ "uartEnable", "group__uart__api.html#ga24c4596f5bda4f7b201e12858507cce4", null ],
    [ "uartGetBaudrate", "group__uart__api.html#gae3488820c7fded9d59b7e7c7757e3d52", null ],
    [ "uartGetParity", "group__uart__api.html#ga9ba5c4fa51177250014cd7a0e17dea02", null ],
    [ "uartGetRxStatus", "group__uart__api.html#ga55bf9529921b5d355278c0898f38da5f", null ],
    [ "uartGetStopBits", "group__uart__api.html#gac82e75704244c025461dc68bd4ed2189", null ],
    [ "uartGetTxStatus", "group__uart__api.html#ga4949da8a62930237f0bc02d21e4acf56", null ],
    [ "uartInit", "group__uart__api.html#ga639170ef5b45f9d2ea25f56e946e1b96", null ],
    [ "uartSend", "group__uart__api.html#ga051a7b49552f579e2f5fdfbc94a78ceb", null ],
    [ "uartSetBaudrate", "group__uart__api.html#ga9b47c1a616c37790b34300a636ccb445", null ],
    [ "uartSetParity", "group__uart__api.html#ga0f217f9a9f964a483ba574e67ffb2ec6", null ],
    [ "uartSetReceiveCB", "group__uart__api.html#gab0b7b354b0d71f0c24c94b59d7f1e813", null ],
    [ "uartSetStopBits", "group__uart__api.html#ga9db90a3bb5f0f9f21da783ce7e93df6d", null ]
];