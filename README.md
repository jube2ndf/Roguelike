Roguelike
О проекте
Roguelike — это 2D Action Roguelike, разработанный на C++ с использованием SFML и собственного игрового движка.
Проект включает собственную реализацию:
•	Component-based архитектуры.
•	SceneManager.
•	EventBus.
•	Collision System.
•	Physics System.
•	Combat System.
•	Enemy AI.
•	Weapon Factory.
•	Audio Manager.
•	Texture Manager.
•	Logger.
Игрок исследует уровни, сражается с противниками и боссами, используя различные виды атак и оружия.
Вдохновением для боевой системы является игра Tale of Immortal.
________________________________________
Возможности
Игрок
•	Передвижение по карте.
•	Базовая атака.
•	Система здоровья.
•	Система брони.
Враги
•	Обнаружение игрока.
•	Преследование цели.
•	Атака по кулдауну.
•	Получение урона.
Игровой движок
•	GameObject / Component система.
•	BoxCollider и CircleCollider.
•	Trigger-система.
•	EventBus.
•	SceneManager.
•	Resource Managers.
•	Audio System.
•	Logging System.
________________________________________
Сборка проекта
Требования
•	Visual Studio 2022
•	C++20
•	SFML 3.1
Сборка
1.	Клонировать репозиторий:
git clone <repository_url>
2.	Открыть решение в Visual Studio.
3.	Убедиться, что SFML находится в каталоге:
SFML-3.1.0
рядом с файлом решения.
4.	Выбрать конфигурацию:
Release x64
или
Debug x64
5.	Собрать решение:
Build → Build Solution
________________________________________
Запуск
После сборки запустить:
bin/Game/x64/Release/Roguelike.exe
или
bin/Game/x64/Debug/Roguelike.exe
в зависимости от конфигурации сборки.
________________________________________
Управление
Клавиша	Действие
W A S D	Передвижение
ЛКМ
1 3
2	Атака
Передвижение по инвентарю
 Использовать предмет из инвентаря
	
________________________________________
Структура проекта
Engine/
 ├─ Core
 ├─ Scene
 ├─ Physics
 ├─ Rendering
 ├─ Audio/Texture
 └─ Events

Roguelike/
 ├─ Player
 ├─ Enemy
 ├─ Combat
 ├─ Weapons
 ├─ Levels
 └─ items
________________________________________
Автор
Разработка: JUbEndF
