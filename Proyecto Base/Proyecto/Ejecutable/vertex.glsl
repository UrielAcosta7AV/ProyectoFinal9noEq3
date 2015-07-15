
attribute vec3 aVertexPosition;
attribute vec2 aTextureCoord;

varying vec2 vTextureCoord;


void main() {
	vTextureCoord = aTextureCoord.xy;
	gl_Position = gl_ModelViewProjectionMatrix * vec4( aVertexPosition.x, aVertexPosition.y, aVertexPosition.z, 1.0f );
}
