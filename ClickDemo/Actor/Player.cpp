#include "Player.h"
#include "Engine/Engine.h"
#include "../Algorithm/AStar.h"
#include"../Algorithm/Node.h"

class Node;

Player::Player()
	: DrawableActor("e")
{
	color = Color::Green;
	position = Vector2(5, 5);
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

    if (Engine::Get().GetKeyDown(VK_RBUTTON))
    {
        // 현재 마우스 위치를 목표 위치로 설정
        Vector2 goalPosition = Engine::Get().MousePosition();

        //// 그리드 생성 (임시로 10x10 크기의 그리드 사용)
        //std::vector<std::vector<int>> grid(10, std::vector<int>(10, 0));

        //// A* 알고리즘 실행
        //AStar aStar;
        //Node* startNode = new Node(position);
        //Node* goalNode = new Node(goalPosition);
        //std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

        //// 경로 출력 (디버그용)
        //for (const Node* node : path)
        //{
        //    std::cout << "Path node: (" << node->position.x << ", " << node->position.y << ")\n";
        //}

        //// 첫 번째 경로 노드로 이동 (필요에 따라 수정)
        //if (!path.empty())
        //{
        //    position = path.front()->position;
        //}
    }

}