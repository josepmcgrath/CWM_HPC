/**************************************************
 *                                                *
 * First attempt at a code to calcule lost barley *
 * by A. Farmer                                   *
 * 18/05/18                                       *
 *                                                *
 **************************************************/

// Include any headers from the C standard library here
#include <stdio.h>
#include <stdlib.h>

// Define any constants that I need to use here
#define PI 3.14

// This is where I should put my function prototypes
float area_of_circle(float radius); 
float area_of_ring(float inner_radius, float outer_radius);
float area_of_rectangle(float length, float width);
float cost_of_x_kg_barley(float kg_barley);

// Now I start my code with main()
int main() {

  // In here I need to delare my variables
    int number_of_circles, number_of_rings;
    float *area;
    float *circle_radii;
    float **ring_radii;
    float total_area = 0, loss_in_kg = 0;     
    float field_length = 0, field_width = 0;
    float area_of_field;
    float total_kg_barley;
    float loss_percentage, monetary_loss;
    int i = 0, j = 0;
  
  // Next I need to get input from the user.
  // I'll do this by using a printf() to ask the user to input the radii.
    printf("Number of circles: ");
    scanf("%d", &number_of_circles);

    circle_radii = (float *)malloc(number_of_circles * sizeof(float));
    
    for (i = 0; i < number_of_circles; i++) {
      printf("Enter circle radius %d: ", (i + 1));
      scanf("%f", &circle_radii[i]);
    }

    printf("Number of rings: ");
    scanf("%d", &number_of_rings);

    ring_radii = (float **)malloc(number_of_rings * sizeof(float*));
    for (i = 0; i < number_of_rings; i++) {
      //second index determines if looking at inner or outer ring radius
      ring_radii[i] = (float *)malloc(2 * sizeof(float));
    }

    for(i = 0; i < number_of_rings; i++) {
      printf("Enter ring %d inner and outer radius: ", (i + 1));
      scanf("%f %f", &ring_radii[i][0], &ring_radii[i][1]); 
    }

    area = (float *)malloc((number_of_circles + number_of_rings) * sizeof(float));

  // Now I need to loop through the radii caluclating the area for each
    for (j = 0; j < number_of_circles; j++) {
      area[j] = area_of_circle(circle_radii[j]);
    }
    for (i = 0; i < number_of_rings; i++) {
      area[j + i] = area_of_ring(ring_radii[i][0], ring_radii[i][1]);
    }

  // Next I'll sum up all of the individual areas
    for (i = 0; i < (number_of_circles + number_of_rings); i++) {
      total_area += area[i];
    }

  /******************************************************************
   *                                                                *
   * Now I know the total area I can use the following information: *
   *                                                                *
   * One square meter of crop produces about 135 grams of barley    *
   *                                                                *
   * One kg of barley sells for about 10 pence                      *
   *                                                                *
   ******************************************************************/

  // Using the above I'll work out how much barley has been lost.
    loss_in_kg = total_area*0.135;

  // Finally I'll use a printf() to print this to the screen.
    printf("\nTotal area lossed in m^2 is:\t%f\n", total_area);
    printf("Total loss in kg is:\t\t%f\n", loss_in_kg);

  // Determine size of farmer's field
    printf("Enter the length and width of the field: ");
    scanf("%f %f", &field_length, &field_width);

  // Calculate area of field
    area_of_field = area_of_rectangle(field_length, field_width);

  // Calculate amount of barley for entire field
    total_kg_barley = area_of_field * 0.135;
    printf("Total potential barley production (kg): \t\t%f\n", total_kg_barley);

  // Calculate loss as a percentage
    loss_percentage = (loss_in_kg / total_kg_barley) * 100;
    printf("Total loss as percentage: \t\t%.2f%%\n", loss_percentage);

  // Calculate monetary loss
    monetary_loss = cost_of_x_kg_barley(loss_in_kg);
    printf("Monetary loss: \t\t£%.2f\n", monetary_loss);

  //Free
    free(circle_radii);
    for (i = 0; i < number_of_rings; i++) {
      free(ring_radii[i]);
    }
    free(ring_radii);

  return(0);
}

// I'll put my functions here:

float area_of_circle(float radius) {
  //Calculates the area of a circle
  return PI * radius * radius;
}

float area_of_ring(float inner_radius, float outer_radius) {
  //Calculates the area of a ring
  return (area_of_circle(outer_radius) - area_of_circle(inner_radius));
}

float area_of_rectangle(float length, float width) {
  //Calculates the area of a rectangle
  return length * width;
}

float cost_of_x_kg_barley(float kg_barley) {
  //Calculates the cost of x kg barley
  return .10 * kg_barley;
}
