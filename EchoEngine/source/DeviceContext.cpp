#include "DeviceContext.h"

void 
DeviceContext::destroy() {
	SAFE_RELEASE(m_deviceContext);
}
