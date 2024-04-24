/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:25:26 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 14:25:26 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#define mapWidth 6
#define mapHeight 6

void    raycasting(t_data *data);
{
    t_ray	ray;
	int		x;
	double temps = 0 ; //heure de la trame actuelle
   	double oldTime = 0; //heure de l'image précédente

	x = 0;
	ray = data->ray;

	// data->player.posX = 2;
	// data->player.posY = 2;   // Position de départ x et y
	
   data->player.dirX = -1;
   data->player.dirY = 0; // vecteur de direction initial
   
   data->player.planX = 0;
   data->player.planY = 0,66 ; //la version Raycaster 2D du plan de la caméra
 
	while (x < data->win_width)
	{
		double cameraX = 2 * x / double(data->win_widht) - 1; //coordonnée x dans l'espace de la caméra
    	double rayDirX = dirX + planeX * cameraX;
    	double rayDirY = dirY + planY * caméraX ;
	}
}

/*

deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))


deltaDistX = abs(|rayDir| / rayDirX)
deltaDistY = abs(|rayDir| / rayDirY)

deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)


      //dans quelle case de la carte nous nous trouvons
       int mapX = int(posX);
      int mapY = int(posY);

      //longueur du rayon depuis la position actuelle jusqu'au prochain côté x ou y
       double sideDistX ;
      double faceDistY ;

             //longueur du rayon d'un côté x ou y au double deltaDistX = (rayDirX == 0) suivant côté x ou y
 ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
      double perpWallDist ;

      //dans quelle direction avancer dans la direction x ou y (soit +1 ou -1)
       int stepX;
      int étapeY ;

      int hit = 0 ; //Y a-t-il eu un coup de mur ?
       côté intérieur ; //un mur NS ou EW a-t-il été touché ?
	     //calcule l'étape et la sideDist initiale
       si (rayDirX < 0)
      {
        étapeX = -1 ;
        sideDistX = (posX - mapX) * deltaDistX ;
      }
      autre
      {
        étapeX = 1 ;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX ;
      }
      si (rayDirY < 0)
      {
        étapeY = -1 ;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      autre
      {
        étapeY = 1 ;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }