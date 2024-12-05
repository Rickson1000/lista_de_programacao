#ifndef SCULPTOR_HPP
#define SCULPTOR_HPP

struct Voxel {
  float r,g,b; // Cores
  float a; // Transparencia
  bool show; // Mostrado ou nao
};

class Sculptor {
private:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  /*! \brief
  * Define a cor atual de desenho. 
  */
  void setColor(float r, float g, float b, float alpha);
  /*! \brief
  *Ativa o voxel na posição (x,y,z)
  *(fazendo show = true) e atribui
  *ao mesmo a cor atual de desenho
  */
  void putVoxel(int x, int y, int z);
  /*! \brief
  *Desativa o voxel na posição (x,y,z) (fazendo show = false)
  */
  void cutVoxel(int x, int y, int z);
  /*! \brief
  *Ativa todos os voxels no intervalo x∈[x0,x1],
  *y∈[y0,y1], z∈[z0,z1] e atribui aos
  *mesmos a cor atual de desenho
  */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /*! \brief
  *Desativa todos os voxels no intervalo
  *x∈[x0,x1], y∈[y0,y1], z∈[z0,z1]
  */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /*! \brief
  *Ativa todos os voxels que satisfazem à equação da esfera e atribui 
  *aos mesmos a cor atual de desenho (r,g,b,a)
  */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /*! \brief
  *Desativa todos os voxels que satisfazem à equação da esfera
  */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /*! \brief
  *Ativa todos os voxels que satisfazem à equação do elipsóide e atribui 
  *aos mesmos a cor atual de desenho
  */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /*! \brief
  *Desativa todos os voxels que satisfazem à equação do elipsóide
  */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  
  /*! \brief
  *grava a escultura no formato OFF no arquivo filename
  */
  void writeOFF(const char* filename);
  /*! \brief
  *Avisa que não pode usar valores negativos para as cores
  */
  void aviso();
};
//
#endif //  SCULPTOR_HPP
