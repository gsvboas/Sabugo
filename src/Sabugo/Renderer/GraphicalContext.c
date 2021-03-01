/* ************************************ * START OF FILE * ************************************* */
/* */
/* */
/* */
/* *********************************** * GLOBAL INCLUDES * ************************************ */
#include "Sabugo.h"
#include "Debug/Debug.h"
#include "Core/Log.h"
#include "Renderer/GraphicalContext.h"

#ifdef GLEW_BACKEND
/* **************************** * START OF GLEW IMPLEMENTATION * ****************************** */
#include <GL/glew.h>
/* ********************* * PRIVATE STRUCTURE AND FUNCTION DECLARATIONS * ********************** */
/* ************************* * PRIVATE GLOBAL VARIABLE DECLARATIONS * ************************* */
/* **************************** * PRIVATE FUNCTIONS DEFINITIONS * ***************************** */
void RENDERER_GRAPHICAL_CONTEXT_DEBUG_CALLBACK(SABUGO_ERROR err)
{
    logBegin(err);
    logStr("DEBUG_CALLBACK called in RENDERER/GRAPHICALCONTEXT at");
    switch (err)
    {
	case RENDERER_INIT_GRAPHICAL_CONTEXT_GLEW_INIT_ERROR:
	    logStr("call to glewInit()");
	    break;
	default:
	    break;
    }
    logEnd();
}
/* ************************ * PUBLIC INTERFACE FUNCTIONS DEFINITIONS * ************************ */
void initGraphicalContext()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){

	return;
    }
}
/* ************************************* * END OF FILE * ************************************** */
#endif

