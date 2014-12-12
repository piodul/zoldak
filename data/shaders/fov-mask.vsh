#version 130

uniform vec4 vPlayerPos;
uniform float fExtrusionLength;

void main()
{
	vec4 vDesiredPosition = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec4 vTransformedPlayerPos = gl_ModelViewProjectionMatrix * vPlayerPos;
	vec2 vExtrusionDirection = normalize(vDesiredPosition.xy - vTransformedPlayerPos.xy);

	vDesiredPosition.xy += vExtrusionDirection * fExtrusionLength * gl_MultiTexCoord0.x;
	gl_Position = vDesiredPosition;
}
