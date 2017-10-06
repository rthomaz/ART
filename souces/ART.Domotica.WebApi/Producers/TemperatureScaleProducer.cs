﻿using ART.Infra.CrossCutting.MQ;
using ART.Domotica.WebApi.IProducers;
using RabbitMQ.Client;
using System.Threading.Tasks;
using ART.Domotica.Constant;

namespace ART.Domotica.WebApi.Producers
{
    public class TemperatureScaleProducer : ProducerBase, ITemperatureScaleProducer
    {
        #region constructors

        public TemperatureScaleProducer(IConnection connection) : base(connection)
        {
            Initialize();
        }

        #endregion

        #region public voids

        public async Task GetScales(string session)
        {
            var payload = await SerializationHelpers.SerializeToJsonBufferAsync(session);
            await Task.Run(() => _model.BasicPublish("", TemperatureScaleConstants.GetScalesQueueName, null, payload));
        }

        #endregion

        #region private voids

        private void Initialize()
        {
            _model.QueueDeclare(
                  queue: TemperatureScaleConstants.GetScalesQueueName
                , durable: false
                , exclusive: false
                , autoDelete: true
                , arguments: null);

            _basicProperties.Persistent = true;
        }

        #endregion
    }
}