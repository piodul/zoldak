#version 130

uniform sampler2D sSource;
uniform sampler2D sMask;

uniform vec4 cFogColor;

void main()
{
	vec4 cSource = texture2D(sSource, gl_TexCoord[0].xy);
	float fMask = texture2D(sMask, gl_TexCoord[0].xy).r;

	gl_FragColor = mix(cSource, cFogColor, fMask);
}
