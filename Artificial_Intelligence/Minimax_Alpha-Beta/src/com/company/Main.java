package com.company;

import com.company.players.Player;
import com.company.players.NaivePlayer;
import com.company.players.Player95105454;

/**
 * Created by The_CodeBreakeR on 3/16/17.
 */
public class Main {

    public static void main(String[] args) {
        Player p1 = new Player95105454(1);
        Player p2 = new Player95105454(2);
        Game g = new Game(p1, p2);
        g.start();
    }

}