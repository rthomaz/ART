﻿using System.Web.Http;
using ART.Infra.CrossCutting.WebApi;
using ART.Domotica.WebApi.IProducers;
using System.Threading.Tasks;
using ART.Domotica.Contract;

namespace ART.Domotica.WebApi.Controllers
{
    [Authorize]
    [RoutePrefix("api/dsFamilyTempSensor")]    
    public class DSFamilyTempSensorController : AuthenticatedApiController
    {
        #region private readonly fields

        protected readonly IDSFamilyTempSensorProducer _dsFamilyTempSensorProducer;

        #endregion

        #region constructors

        public DSFamilyTempSensorController(IDSFamilyTempSensorProducer dsFamilyTempSensorProducer) //: base(connection)
        {
            _dsFamilyTempSensorProducer = dsFamilyTempSensorProducer;
        }

        #endregion

        #region public voids

        /// <summary>
        /// Retornar uma lista de sensores
        /// </summary>        
        /// <remarks>
        /// Retornar uma lista de sensores
        /// </remarks>
        /// <param name="contract">contrato do post</param>
        /// <response code="200">OK</response>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("getAll")]
        [HttpPost]
        public async Task<IHttpActionResult> GetAll(DSFamilyTempSensorGetAllContract contract)
        {
            await _dsFamilyTempSensorProducer.GetAll(contract);
            return Ok();
        }

        /// <summary>
        /// Retornar uma lista de Resoluções
        /// </summary>        
        /// <remarks>
        /// Retornar uma lista de Resoluções
        /// </remarks>
        /// <param name="session">session do broker do solicitante</param>
        /// <response code="200">OK</response>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("getResolutions")]
        [HttpPost]
        public async Task<IHttpActionResult> GetResolutions(DSFamilyTempSensorGetResolutionsContract contract)
        {           
            await _dsFamilyTempSensorProducer.GetResolutions(contract);
            return Ok();
        }

        /// <summary>
        /// Altera a resolução de um sensor
        /// </summary>
        /// <remarks>
        /// Altera a resolução de um sensor
        /// </remarks>
        /// <param name="request">model do request</param>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("setResolution")]
        [HttpPost]
        public async Task<IHttpActionResult> SetResolution(DSFamilyTempSensorSetResolutionContract contract)
        {
            await _dsFamilyTempSensorProducer.SetResolution(contract);
            return Ok();
        }

        /// <summary>
        /// Altera o alarme alto de um sensor
        /// </summary>
        /// <remarks>
        /// Altera o alarme alto de um sensor
        /// </remarks>
        /// <param name="request">model do request</param>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("setHighAlarm")]
        [HttpPost]
        public async Task<IHttpActionResult> SetHighAlarm(DSFamilyTempSensorSetHighAlarmContract contract)
        {
            await _dsFamilyTempSensorProducer.SetHighAlarm(contract);
            return Ok();
        }

        /// <summary>
        /// Altera o alarme baixo de um sensor
        /// </summary>
        /// <remarks>
        /// Altera o alarme baixo de um sensor
        /// </remarks>
        /// <param name="request">model do request</param>
        /// <response code="400">Bad Request</response>
        /// <response code="403">Forbidden</response>
        /// <response code="500">Internal Server Error</response>
        [Route("setLowAlarm")]
        [HttpPost]
        public async Task<IHttpActionResult> SetLowAlarm(DSFamilyTempSensorSetLowAlarmContract contract)
        {
            await _dsFamilyTempSensorProducer.SetLowAlarm(contract);
            return Ok();
        }

        #endregion
    }
}