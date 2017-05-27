Angel.h, CheckError, mat.h, vec.h
	shader를 구현하는데 필요한 헤더들이다.

InitShader
	shader program을 불러오는데 필요한 코드가 들어있다.

vshader.glsl, fshader.glsl
	shader program이 구현되어있다.

Game.h, Game.cpp
	게임 전체를 운영하는 class GAME이 선언되어있다. 맵 관련 헤더와 캐릭터 관련 헤더를 include하고 있다.

Map.h Map.cpp
	맵을 관리하는 class MAP이 선언되어있다. 들판, 도로, 강을 다루기 때문에 이와 관련된 RRF.h를 include하고 있다.

RRF.h RRF.cpp
	들판, 도로, 강을 다루는 각각 class FIELD, class ROAD, class RIVER가 선언되어있다.
	나무와 자동차, 그리고 통나무를 관리해야하기 때문에 이와 관련된 CLT.h가 include 되어있다.

CLT.h CLT.cpp
	자동차, 통나무, 나무를 다루는 각각 class CAR, class LOG, class TREE가 선언되어있다.
	Angel.h를 include하고 있다.

Player.h Player.cpp
	캐릭터를 관리하는 class PLAYER가 선언되어있다.


캐릭터 조작은 방향키로 한다.
시점 변환은 숫자키로 하는데, 각각
1은 위에서 바라보는 시점,
2는 캐릭터 뒤에서 바라보는 시점,
3은 캐릭터의 시점이다.