﻿using System.Threading.Tasks;
using RabbitMQ.Client;
using ART.Infra.CrossCutting.MQ.Contract;
using ART.Infra.CrossCutting.MQ.Producer;
using ART.Domotica.Producer.Interfaces;
using ART.Domotica.Constant;
using ART.Infra.CrossCutting.Utils;

namespace ART.Domotica.Producer.Services
{
    public class ApplicationBrokerSettingProducer : ProducerBase, IApplicationBrokerSettingProducer
    {
        #region constructors

        public ApplicationBrokerSettingProducer(IConnection connection) : base(connection)
        {
            Initialize();
        }

        #endregion

        #region public voids

        public async Task Get(AuthenticatedMessageContract message)
        {
            await Task.Run(() => 
            {
                var payload = SerializationHelpers.SerializeToJsonBufferAsync(message);
                _model.BasicPublish("", ApplicationBrokerSettingConstants.GetQueueName, null, payload);
            });            
        }

        #endregion

        #region private voids

        private void Initialize()
        {
            _model.QueueDeclare(
                  queue: ApplicationBrokerSettingConstants.GetQueueName
                , durable: false
                , exclusive: false
                , autoDelete: true
                , arguments: null);
        }

        #endregion
    }
}