// ejercicio 3 "EL CAOS DE LOS DESCUENTOS"


#include <iostream>


int main() {
    
  std::string VIP;
  
  int productos;
  
 
  
  std::cout<< "¿El cliente es VIP? (si/no) : ";
   
    std::cin >> VIP;
   
    
   if (VIP =="si" ){
       std::cout << "tienes un descuento del 20% ";
       
   } else {
       
       std::cout << "ingrese la cantidad de productos ";
       
       std::cin >> productos;
       
       if(productos >=4){
           std::cout << "tienes un 10% de descuento";
       }else{
           std::cout << "no tienes decuento";
       }
   }     
       
       
   
    
   
    
    return 0;
    

}






