Angel.h, CheckError, mat.h, vec.h
	shader를 구현하는데 필요한 헤더들이다.

InitShader
	shader program을 불러오는데 필요한 코드가 들어있다.

vshader.glsl, fshader.glsl
	기본적인 modeling을 불러오는 shader program이 구현되어있다.

vfbo.glsl, ffbo.glsl
	filter를 구현한 shader program이 구현되어있다.

lodepng.h, lodepng.cpp
	png파일을 불러오는 함수로, 인터넷에서 구한 소스이다.

texture.h, texture.cpp
	lodepng에서 불러온 정보를 이용해 texture buffer를 만드는 역할을 한다. class로 구현되어있다.

main.cpp
	전체적인 model을 그리고, shader에 불러와 값을 넣어주는 역할을 한다.

field.h, field.cpp
	modeling을 구성하는 각 요소들을 class로 가지고 있다.

building.h, building.cpp
	field에 세워지는 building들을 관리한다.

car.h, car.cpp
	field의 도로 위에서 돌아다닐 car들을 관리한다.

m을 누르면 filter가 바뀐다.
순서대로
흑백, 반전, 모자이크, 블러, 만화, 어안렌즈, 충격파, 유리 순이다.
마우스 드래그를 이용하여 영역을 지정해주면 해당 영역에만 filter가 적용된다. 단 드래그를 하지 않을 경우에는 영역의 넓이를 0으로 인식하여 filter가 적용되지 않는다. 초기화를 위해서는 마우스 오른쪽 버튼을 누르면 된다.
방향키를 이용하여 시점을 움직일 수 있다.