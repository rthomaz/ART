﻿'use strict';
app.factory('numericalScaleTypeService', ['$http', 'ngAuthSettings', '$rootScope', 'stompService', 'siContext', function ($http, ngAuthSettings, $rootScope, stompService, siContext) {

    var serviceBase = ngAuthSettings.distributedServicesUri;

    var _initializing = false;
    var _initialized  = false;

    var serviceFactory = {};    

    var onConnected = function () {

        stompService.subscribe('SI.NumericalScaleType.GetAllViewCompleted', onGetAllCompleted);

        if (!_initializing && !_initialized) {
            _initializing = true;
            getAll();
        }
    }   

    var initialized = function () {
        return _initialized;
    };

    var getAll = function () {
        return $http.post(serviceBase + 'api/si/numericalScaleType/getAll').then(function (results) {
            //alert('envio bem sucedido');
        });
    };       

    var onGetAllCompleted = function (payload) {
        var dataUTF8 = decodeURIComponent(escape(payload.body));
        var data = JSON.parse(dataUTF8);
        for (var i = 0; i < data.length; i++) {
            siContext.numericalScaleTypes.push(data[i]);
        }
        siContext.numericalScaleTypeLoaded = true;
        _initializing = false;
        _initialized = true;
        clearOnConnected();
        $rootScope.$emit('numericalScaleTypeService_Initialized');
    }

    $rootScope.$on('$destroy', function () {
        clearOnConnected();
    });

    var clearOnConnected = $rootScope.$on('stompService_onConnected', onConnected);        

    // stompService
    if (stompService.connected())
        onConnected();

    // serviceFactory

    serviceFactory.initialized = initialized;

    return serviceFactory;

}]);