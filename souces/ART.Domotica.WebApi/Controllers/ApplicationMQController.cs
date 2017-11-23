﻿namespace ART.Domotica.WebApi.Controllers
{
    using System.Web.Http;
    using ART.Infra.CrossCutting.MQ.WebApi;
    using System.Threading.Tasks;
    using ART.Domotica.Producer.Interfaces;
    using System.Web.Http.Description;
    using ART.Domotica.Contract;

    [Authorize]
    [RoutePrefix("api/applicationMQ")]
    public class ApplicationMQController : AuthenticatedMQApiControllerBase
    {
        #region Fields

        protected readonly IApplicationMQProducer _applicationMQProducer;

        #endregion Fields

        #region Constructors

        //: base(connection)
        public ApplicationMQController(IApplicationMQProducer applicationMQProducer)
        {
            _applicationMQProducer = applicationMQProducer;
        }

        #endregion Constructors

        #region public voids

        /// <summary>
        /// Retornar as configurações do broker da aplicação Web
        /// </summary>        
        /// <remarks>
        /// Retornar as configurações do broker da aplicação Web
        /// </remarks>
        /// <response code="200">OK</response>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("get")]
        [HttpPost]
        [ResponseType(typeof(ApplicationMQGetRPCResponseContract))]
        public async Task<IHttpActionResult> Get()
        {
            var result = await _applicationMQProducer.GetRPC(CreateMessage());
            return Ok(result);
        }

        #endregion
    }
}