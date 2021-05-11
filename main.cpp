#include <chrono>
#include <cmath>
#include <cstdio>
#include <windows.h>

#include "map.hpp"
#include "player.hpp"

const int screenWidth = 120;
const int screenHeight = 40;

int main()
{
  Map map;
  Player player;
  wchar_t* screen = new wchar_t[screenWidth * screenHeight + 1];
  screen[screenHeight * screenHeight] = '\0';

  HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
  SetConsoleActiveScreenBuffer(hConsole);
  DWORD dwBytesWritten = 0;

  auto time = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - time;

  while (true)
  {
    elapsedTime = std::chrono::system_clock::now() - time;
    time = std::chrono::system_clock::now();

    if (GetAsyncKeyState('A')) //A left
    {
      player.rotate(-player.getRotationSpeed() * elapsedTime.count());
    }
    if (GetAsyncKeyState('D')) //D right
    {
      player.rotate(player.getRotationSpeed() * elapsedTime.count());
    }
    if (GetAsyncKeyState('W')) //W front
    {
      point_t playerPosition = {
        player.position().x + std::sin(player.getViewDirectionAngle()) * player.getSpeed() * elapsedTime.count(),
        player.position().y + std::cos(player.getViewDirectionAngle()) * player.getSpeed() * elapsedTime.count()};

      if (!map.checkWall(playerPosition))
      {
        player.moveTo(playerPosition);
      }
    }
    if (GetAsyncKeyState('S')) //S back
    {
      point_t playerPosition = {
        player.position().x - std::sin(player.getViewDirectionAngle()) * player.getSpeed() * elapsedTime.count(),
        player.position().y - std::cos(player.getViewDirectionAngle()) * player.getSpeed() * elapsedTime.count()};

      if (!map.checkWall(playerPosition))
      {
        player.moveTo(playerPosition);
      }
    }

    if (GetAsyncKeyState('X')) //X exit
    {
      break;
    }

    //Ray casting
    for (int x = 0; x < screenWidth; ++x)
    {
      double rayAngle = (player.getViewDirectionAngle() - player.getFOV() / 2) + (player.getFOV() * x / screenWidth);
      point_t rayCoordinate{sin(rayAngle), cos(rayAngle)};
      double rayLength = 0;

      while (rayLength < player.getVisibilityRange())
      {
        rayLength += 0.1;

        int testX = static_cast<int>(player.position().x + rayCoordinate.x * rayLength);
        int testY = static_cast<int>(player.position().y + rayCoordinate.y * rayLength);

        if (testX < 0 || testX >= map.getWidth() || testY < 0 || testY >= map.getHeight())
        {
          rayLength = player.getVisibilityRange();
          break;
        }
        else if (map.checkWall({static_cast<double>(testX), static_cast<double>(testY)}))
        {
          break;
        }
      }

      int celling = static_cast<int>(static_cast<double>(screenHeight) / 2.0 -
        static_cast<double>(screenHeight) / rayLength);
      int floor = screenHeight - celling;

      int y = 0;

      if (celling < 0 || floor > screenHeight)
      {
        celling = 0;
        floor = screenHeight;
      }

      short wallSymbol;
      if (static_cast<int>(rayLength) <= player.getVisibilityRange() / 4)
      {
        wallSymbol = 0x2588;
      }
      else if (static_cast<int>(rayLength) <= player.getVisibilityRange() / 2)
      {
        wallSymbol = 0x2593;
      }
      else
      {
        wallSymbol = 0x2591;
      }


      for (; y < celling; ++y)
      {
        screen[x + y * screenWidth] = ' ';
      }
      for (; y < floor; ++y)
      {
        screen[x + y * screenWidth] = wallSymbol;
      }
      for (; y < screenHeight; ++y)
      {
        screen[x + y * screenWidth] = '.';
      }
    }

    swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", player.position().x, player.position().y,
      player.getViewDirectionAngle(), 1.0f / elapsedTime.count());

    WriteConsoleOutputCharacterW(hConsole, screen, screenWidth * screenHeight, {0, 0}, &dwBytesWritten);
  }
}
