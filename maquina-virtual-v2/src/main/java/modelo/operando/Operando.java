/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

/**
 *
 * @author valen
 */
public abstract class Operando
{
    public abstract TipoOperando getTipo();
    
    @Override
    public abstract String toString();
    
    public static Operando creaOperando(int tipoOpernado, int operando)
    {
        Operando nuevo;
        nuevo = switch (tipoOpernado)
        {
            case 1 -> new OperandoRegistro(operando);
            case 2 -> new OperandoInmediato(operando);
            default -> new OperandoMemoria(operando);
        };
        return nuevo;
    }
}
