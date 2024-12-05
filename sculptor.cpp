#include "sculptor.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>

std::ofstream fout;

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx;
  ny = _ny;
  nz = _nz;
  v = new Voxel **[nx];

  for (int x = 0; x < nx; x++) {
    v[x] = new Voxel *[ny];
  }
  for (int x = 0; x < nx; x++) {
    for (int y = 0; y < ny; y++) {
      v[x][y] = new Voxel[nz];
    }
  }
}

Sculptor::~Sculptor() {
  delete[] v[0][0];
  delete[] v[0];
  delete v;
}

void Sculptor::setColor(float r, float g, float b, float alpha) {
  if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255) ||
      (alpha < 0 || alpha > 1)) {
    Sculptor::aviso();
  } else {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
  }
}
void Sculptor::putVoxel(int x, int y, int z) {
  if ((x < 0 || x > nx) || (y < 0 || y > ny) || (z < 0 || z > nz)) {
    Sculptor::aviso();
  } else {
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
    v[x][y][z].show = true;
  }
}
void Sculptor::cutVoxel(int x, int y, int z) {
  if ((x < 0 || x > nx) || (y < 0 || y > ny) || (z < 0 || z > nz)) {
    Sculptor::aviso();
  } else {
    v[x][y][z].show = false;
  }
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        Sculptor::putVoxel(i, j, k);
      }
    }
  }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        Sculptor::cutVoxel(i, j, k);
      }
    }
  }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if ((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) <
            (pow(radius, 2))) {
          Sculptor::putVoxel(i, j, k);
        }
      }
    }
  }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2) <
            (pow(radius, 2))) {
          Sculptor::cutVoxel(i, j, k);
        }
      }
    }
  }
}
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (pow((i - xcenter), 2) / (rx * rx) + pow((j - ycenter), 2) / (ry * ry) + pow((k - zcenter), 2) / (rz * rz) < 1) {
          Sculptor::putVoxel(i, j, k);
        }
      }
    }
  }
}
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (pow((i - xcenter), 2) / (rx * rx) + pow((j - ycenter), 2) / (ry * ry) + pow((k - zcenter), 2) / (rz * rz) < 1) {
          Sculptor::cutVoxel(i, j, k);
        }
      }
    }
  }
}
void Sculptor::writeOFF(const char *foutname) {

  int contShow = 0; // auxiliar para contar o total de voxels show = true
  int coordenada = 0;
  float lado = 0.5;
  fout.open(foutname);
  if (!fout.is_open()) {
    exit(1);
  }
  fout << "OFF"
       << "\n";
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          contShow++;
        }
      }
    }
  }

  fout << contShow * 8 << " " << contShow * 6 << " 0\n";

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {

        if (v[i][j][k].show) {
          fout << i - lado << " " << j + lado << " " << k - lado << "\n"
               << std::flush;
          fout << i - lado << " " << j - lado << " " << k - lado << "\n"
               << std::flush;
          fout << i + lado << " " << j - lado << " " << k - lado << "\n"
               << std::flush;
          fout << i + lado << " " << j + lado << " " << k - lado << "\n"
               << std::flush;
          fout << i - lado << " " << j + lado << " " << k + lado << "\n"
               << std::flush;
          fout << i - lado << " " << j - lado << " " << k + lado << "\n"
               << std::flush;
          fout << i + lado << " " << j - lado << " " << k + lado << "\n"
               << std::flush;
          fout << i + lado << " " << j + lado << " " << k + lado << "\n"
               << std::flush;
        }
      }
    }
  }

  contShow = 0;

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          coordenada = contShow * 8;
          // 1°
          fout << 4 << " " << coordenada + 0 << " " << coordenada + 3 << " "
               << coordenada + 2 << " " << coordenada + 1 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";
          // 2°
          fout << 4 << " " << coordenada + 4 << " " << coordenada + 5 << " "
               << coordenada + 6 << " " << coordenada + 7 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";
          // 3°
          fout << 4 << " " << coordenada + 0 << " " << coordenada + 1 << " "
               << coordenada + 5 << " " << coordenada + 4 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";
          // 4°
          fout << 4 << " " << coordenada + 0 << " " << coordenada + 4 << " "
               << coordenada + 7 << " " << coordenada + 3 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";
          // 5°
          fout << 4 << " " << coordenada + 3 << " " << coordenada + 7 << " "
               << coordenada + 6 << " " << coordenada + 2 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";
          // 6°
          fout << 4 << " " << coordenada + 1 << " " << coordenada + 2 << " "
               << coordenada + 6 << " " << coordenada + 5 << std::fixed;
          fout << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
               << v[i][j][k].b << " " << v[i][j][k].a << "\n";

          contShow++;
        }
      }
    }
  }
  fout.close();
}
void Sculptor::aviso() {
  std::cout << "DEU ERRO!!!" << "\n";
}
