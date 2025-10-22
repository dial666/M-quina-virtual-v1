/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.Contexto;
import modelo.excepciones.SegmentationFaultException;

/**
 *
 * @author valen
 */
public class OperandoFactory
{
    public OperandoFactory()
    {
        
    }
    
    public Operando creaOperando(int tipo, int operando)
    {
        Operando op = null;
        switch (tipo)
        {
            case 1 ->
            {
                int codSector = (operando >> 6) & 0b11;
                int codRegistro = operando & 0x1F;
                switch (codSector)
                {
                    case 0 ->
                    {
                        op = new OperandoRegistroE(codRegistro);
                    }
                    case 1 ->
                    {
                        op = new  OperandoRegistroL(codRegistro);
                    }
                    case 2 ->
                    {
                        op = new OperandoRegistroH(codRegistro);
                    }
                    case 3 ->
                    {
                        op = new OperandoRegistroX(codRegistro);
                    }
                    default -> throw new IllegalArgumentException("el operando de registro no tiene un codigo de sector valido");
                }
            }
            case 2 ->
            {
                op = new OperandoInmediato(operando);
            }
            case 3 ->
            {
                int codTamCelda = (operando >> 22) & 0b11;
                
                if (codTamCelda == 0b01)
                    throw new IllegalArgumentException("el operando de memoria no tiene un codigo de tamanio de celda valido");
                
                int codRegistro = (operando >> 16) & 0x1F;
                int offset = (operando << 16) >> 16;
                op = new OperandoMemoria(codTamCelda, new OperandoRegistroE(codRegistro), offset);
            }
            default -> throw new IllegalArgumentException("el tipo de operando no es valido");
        }
        return op;
    }
}
