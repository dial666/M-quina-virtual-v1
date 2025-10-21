/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

/**
 *
 * @author valen
 */
public class Operacion
{
    private ConstantesOperaciones tipoOperacion;
    
    public Operacion(int codOperacion)
    {
        this.tipoOperacion = ConstantesOperaciones.getTipoOperacion(codOperacion);
    }

    public ConstantesOperaciones getTipoOperacion()
    {
        return this.tipoOperacion;
    }
    
    @Override
    public String toString()
    {
        return ConstantesOperaciones.getNombre(tipoOperacion);
    }
}
