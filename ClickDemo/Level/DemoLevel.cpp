#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Actor/Start.h"
#include "Actor/Player.h"
#include <iostream>

DemoLevel::DemoLevel() {
    // �÷��̾�� ���� ���͸� �߰�
    DrawableActor* start = new Start();
    actors.push_back(start);

    DrawableActor* player = new Player();
    actors.push_back(player);

    // �׸��� �ʱ�ȭ
    for (int x = 0; x < grid[0].size(); ++x) {
        for (int y = 0; y < grid.size(); ++y) {
            if (grid[y][x] == 2) {
                actors[0]->SetPosition(Vector2(x, y));  // ���� ��ġ
            }
            else if (grid[y][x] == 3) {
                actors[1]->SetPosition(Vector2(x, y));  // ��ǥ ��ġ
            }
        }
    }
}

void DemoLevel::Update(float deltaTime) {
    Super::Update(deltaTime);

    // ���콺 Ŭ�� ó��: ������ �̵�
    if (Engine::Get().GetKeyDown(VK_LBUTTON)) {
        Vector2 mousePosition = Engine::Get().MousePosition();

        // ���� ������ ����
        for (int x = 0; x < grid[0].size(); ++x) {
            for (int y = 0; y < grid.size(); ++y) {
                if (grid[y][x] == 2) {
                    grid[y][x] = 0;
                }
            }
        }

        // �� ��ġ�� ������ ����
        actors[0]->SetPosition(mousePosition);
        int newX = static_cast<int>(mousePosition.x);
        int newY = static_cast<int>(mousePosition.y);

        if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
            grid[newY][newX] = 2;
        }
    }

    // ���콺 Ŭ�� ó��: ��ǥ�� �̵�
    if (Engine::Get().GetKeyDown(VK_RBUTTON)) {
        Vector2 mousePosition = Engine::Get().MousePosition();

        // ���� ��ǥ�� ����
        for (int x = 0; x < grid[0].size(); ++x) {
            for (int y = 0; y < grid.size(); ++y) {
                if (grid[y][x] == 3) {
                    grid[y][x] = 0;
                }
            }
        }

        // �� ��ġ�� ��ǥ�� ����
        actors[1]->SetPosition(mousePosition);
        int newX = static_cast<int>(mousePosition.x);
        int newY = static_cast<int>(mousePosition.y);

        if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
            grid[newY][newX] = 3;
        }
    }

    // F1 Ű�� ������ A* ��� Ž�� ����
    if (Engine::Get().GetKeyDown(VK_F1)) {
        Node* startNode = nullptr;
        Node* goalNode = nullptr;

        // ���� ���� ��ǥ ��� �˻�
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

        // A* �˰��� ��ü ���� �� ��� Ž��
        AStar aStar;
        std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

        if (!path.empty()) {
            // ��� ���
            aStar.DisplayGridWithPath(grid, path);

            // ��� ǥ�� Ÿ�̸� ����
            path_display.StartTimer();
        }
        else {
            std::cout << "��θ� ã�� ���߽��ϴ�.\n";
        }

        // �޸� ����
        SafeDelete(goalNode);
    }

     //��ΰ� 2�ʰ� ǥ�õ� �� �����ǵ��� ó��
    if (path_display.EndTimer()) {
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[0].size(); ++x) {

                //*�� �������� ����
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
