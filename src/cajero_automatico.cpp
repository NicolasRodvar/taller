// ejercicio 4 "el cajero"


    #include <iostream>
    
    
    int main(){
        
        
      int pinCorrecto = 1234;     //se usa un pin fijo como ejemplo para el ejercicio  
      
      int pinIngresado;
      
      int saldo = 1000;        //tambien para el ejemplo
      
      int opcion, monto;  
        
        
        std::cout<< "ingrese su pin ";
        
        std::cin >> pinIngresado;
        
        if (pinIngresado != pinCorrecto) {   //el ! antes del = es para decir que es "no igual"
            
            std::cout << "Pin incorrecto su cuenta a sido Bloqueada "<< std::endl;
        
            
        }else {
            
            std::cout << "pin Correcto"<< std::endl;
            std::cout << "------MENU------"<< std::endl;
            std::cout << "1. Consultar saldo "<< std::endl;
            std::cout << "2. Retirar Dinero" << std::endl;
            std::cout << "Elija una opcion" << std::endl;
            std::cin >> opcion;
            
        }  if (opcion == 1 ){
            std::cout << "su saldo es de $" << saldo << std::endl;
            std::cout << "¿desea retirar?"<< std::endl;
            std::cout << "si desea retirar oprima (2)";
            std::cin >> opcion;
            if (opcion == 2) {
                std::cout << "ingrese monto a retirar"<<std::endl;
                std::cout << " $";
                std::cin >> monto;
                if ( monto <=saldo){
                    saldo -= monto;
                    std::cout << "ha retirado $"<<monto<<std::endl;
                    std::cout<<"su nuevo saldo es $"<< saldo<< std::endl;
                }
                
                
            }
        }else if (opcion == 2 ) {
            std::cout<< "ingrese monto a retirar"<<std::endl;
            std::cout<< " $";
            std::cin >> monto;
            
            if (monto <=saldo){
                saldo -= monto;
                std::cout << "ha retirado $"<<monto<< std::endl;
                std::cout<< "su nuevo saldo es de $"<< saldo<< std::endl;
                
            }else{
                std::cout<< "saldo insuficiente";
            }
            
        }
        
            
            
            
            
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        return 0;
    }
    
    
  








