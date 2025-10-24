/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.jump;

/**
 *
 * @author valen
 */
public class Jnn extends OperacionJump
{

    @Override
    public boolean saltar()
    {
        return this.jmpIf(0, 1) || this.jmpIf(0, 0);
    }

    @Override
    public String toString()
    {
        return "JNN";
    }
    
    
}
