#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Actor/Start.h"
#include "Actor/Player.h"
#include <iostream>

DemoLevel::DemoLevel() {
    // 플레이어와 시작 액터를 추가
    DrawableActor* start = new Start();
    actors.push_back(start);

    DrawableActor* player = new Player();
    actors.push_back(player);

    // 그리드 초기화
    for (int x = 0; x < grid[0].size(); ++x) {
        for (int y = 0; y < grid.size(); ++y) {
            if (grid[y][x] == 2) {
                actors[0]->SetPosition(Vector2(x, y));  // 시작 위치
            }
            else if (grid[y][x] == 3) {
                actors[1]->SetPosition(Vector2(x, y));  // 목표 위치
            }
        }
    }
}

void DemoLevel::Update(float deltaTime) {
    Super::Update(deltaTime);

    // 마우스 클릭 처리: 시작점 이동
    if (Engine::Get().GetKeyDown(VK_LBUTTON)) {
        Vector2 mousePosition = Engine::Get().MousePosition();

        // 이전 시작점 제거
        for (int x = 0; x < grid[0].size(); ++x) {
            for (int y = 0; y < grid.size(); ++y) {
                if (grid[y][x] == 2) {
                    grid[y][x] = 0;
                }
            }
        }

        // 새 위치에 시작점 설정
        actors[0]->SetPosition(mousePosition);
        int newX = static_cast<int>(mousePosition.x);
        int newY = static_cast<int>(mousePosition.y);

        if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
            grid[newY][newX] = 2;
        }
    }

    // 마우스 클릭 처리: 목표점 이동
    if (Engine::Get().GetKeyDown(VK_RBUTTON)) {
        Vector2 mousePosition = Engine::Get().MousePosition();

        // 이전 목표점 제거
        for (int x = 0; x < grid[0].size(); ++x) {
            for (int y = 0; y < grid.size(); ++y) {
                if (grid[y][x] == 3) {
                    grid[y][x] = 0;
                }
            }
        }

        // 새 위치에 목표점 설정
        actors[1]->SetPosition(mousePosition);
        int newX = static_cast<int>(mousePosition.x);
        int newY = static_cast<int>(mousePosition.y);

        if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
            grid[newY][newX] = 3;
        }
    }

    // F1 키가 눌리면 A* 경로 탐색 시작
    if (Engine::Get().GetKeyDown(VK_F1)) {
        Node* startNode = nullptr;
        Node* goalNode = nullptr;

        // 시작 노드와 목표 노드 검색
        for (int x = 0; x < grid[0].size(); ++x) {
            for (int y = 0; y < grid.size(); ++y) {
                if (grid[y][x] == 2) {
                    startNode = new Node(Vector2(x, y));
                }
                if (grid[y][x] == 3) {
                    goalNode = new Node(Vector2(x, y));
                }
            }
        }

        // A* 알고리즘 객체 생성 및 경로 탐색
        AStar aStar;
        std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

        if (!path.empty()) {
            // 경로 출력
            aStar.DisplayGridWithPath(grid, path);

            // 경로 표시 타이머 시작
            path_display.StartTimer();
        }
        else {
            std::cout << "경로를 찾지 못했습니다.\n";
        }

        // 메모리 해제
        SafeDelete(goalNode);
    }

     //경로가 2초간 표시된 후 삭제되도록 처리
    if (path_display.EndTimer()) {
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[0].size(); ++x) {

                //*을 공백으로 변경
                if (grid[y][x] == 4) {
                    grid[y][x] = 0;
                }
            }
        }
    }
}

void DemoLevel::Draw() {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            if (grid[y][x] == 0) {
                Engine::Get().Draw(Vector2(x, y), " ", Color::White);
            }
            else if (grid[y][x] == 1) {
                Engine::Get().Draw(Vector2(x, y), "1", Color::Blue);
            }
            else if (grid[y][x] == 2) {
                Engine::Get().Draw(Vector2(x, y), "s", Color::Red);
            }
            else if (grid[y][x] == 3) {
                Engine::Get().Draw(Vector2(x, y), "e", Color::Red);
            }
            else if (grid[y][x] == 4) {
                Engine::Get().Draw(Vector2(x, y), "*", Color::Green);
            }
        }
    }

    Super::Draw();
}
