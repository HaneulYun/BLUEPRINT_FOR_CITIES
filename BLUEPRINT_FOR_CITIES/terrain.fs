#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec4 ShadowCoord;

in vec3 toLightVector[16];

layout(location = 0) out vec3 color;

uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
uniform sampler2DShadow shadowMap;

uniform vec3 lightPosition[16];
uniform int lightNum;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main(){
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 500.0f;
	vec3 streetLightColor = vec3(250.f/255,160.f/255,12.f/255);
	float streetLightPower = 5.0f;
	
	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);
	
	vec3 MaterialDiffuseColor = vec3(89.0/255,90.0/255,44.0/255);
	vec3 MaterialAmbientColor = vec3(0.2,0.2,0.2) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.05,0.05,0.05);

	for(int i = 0; i < 16; ++i){
		float distance = length( lightPosition[i] - Position_worldspace );

		vec3 n = normalize( toLightVector[i] );
		vec3 l = normalize( lightPosition[i] - Position_worldspace );
		float cosTheta = clamp( dot( n,l ), 0,1 );
		
		vec3 E = normalize(EyeDirection_cameraspace);
		vec3 R = reflect(-l,n);
		float cosAlpha = clamp( dot( E,R ), 0,1 );
		
		float visibility=1.0;
		float bias = 0.0005*tan(acos(cosTheta));
		bias = clamp(bias, 0,0.01);

		for (int i=0;i<4;i++){
			int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
			visibility -= 0.2*(1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[index]/700.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
		}

		totalDiffuse += visibility * MaterialDiffuseColor * streetLightColor * streetLightPower * cosTheta / (distance*distance) / 16 ;
		totalSpecular += visibility * MaterialSpecularColor * streetLightColor * streetLightPower * pow(cosAlpha,10) / (distance*distance) / 16;
	}

	float distance = length( LightPosition_worldspace - Position_worldspace );

	vec3 n = normalize( Normal_cameraspace );
	vec3 l = normalize( LightDirection_cameraspace );
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	float visibility=1.0;
	float bias = 0.0005*tan(acos(cosTheta));
	bias = clamp(bias, 0,0.01);

	for (int i=0;i<4;i++){
		int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
		visibility -= 0.2*(1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[index]/700.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
	}
	LightColor += vec3(1,cosTheta ,cosTheta);
	totalDiffuse += visibility * MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) ;
	totalSpecular += visibility * MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,10) / (distance*distance) ;

	color = MaterialAmbientColor + totalDiffuse + totalSpecular;
}