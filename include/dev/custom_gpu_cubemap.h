#ifndef __CUSTOM_GPU_CUBE_MAP_H__
#define __CUSTOM_GPU_CUBE_MAP_H__ 1

#include <vector>
#include <string>

#include "EDK3/referenced.h"

/**
 * @class CustomGPUCubeMap
 * @brief Clase que representa un mapa de cubo personalizado de la GPU.
 *
 * Esta clase hereda de EDK3::Referenced y se utiliza para gestionar un mapa de cubo personalizado en la unidad de procesamiento gráfico (GPU).
 */
class CustomGPUCubeMap : public EDK3::Referenced
{
public:
	/**
	 * @brief Constructor de CustomGPUCubeMap.
	 */
	CustomGPUCubeMap();

	/**
	 * @brief Destructor de CustomGPUCubeMap.
	 */
	~CustomGPUCubeMap();

	/**
	 * @brief Inicializa el mapa de cubo con las texturas especificadas.
	 * @param text Vector de cadenas que representa las rutas de las texturas del mapa de cubo.
	 */
	void init(std::vector<std::string> text);

  /**
	 * @brief Vincula el mapa de cubo a una unidad de textura específica.
	 * @param textUnit Unidad de textura a la que se vincula el mapa de cubo.
	 */
	void bind(unsigned int textUnit) const;

private:
	unsigned int id_;
	int w_;
	int h_;
	int n_;
};

#endif //__CUSTOM_GPU_CUBE_MAP_H__