package com.example.appka

import android.content.DialogInterface
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import java.util.*



class MainActivity : AppCompatActivity() {
    var score = 0;
    var tries = 0;
    val ran = Random();
    var rnd: Int    = ran.nextInt(20);

    fun toast(msg: String) {
        Toast.makeText(applicationContext, msg, Toast.LENGTH_LONG).show();
    }
    fun setRecord() {
        val sharedScore = this.getSharedPreferences("com.example.appka.shared", 0);
        val edit = sharedScore.edit();
        edit.putInt("score", score);
        edit.apply();
    }
    fun getRecord() {
        val sharedScore = this.getSharedPreferences("com.example.appka.shared", 0);
        score = sharedScore.getInt("score", 0);
        updateScore();
    }
    fun updateScore() {
        val points = findViewById<TextView>(R.id.pointField);
        val string = "Punkty: $score";
        points.text = string;
    }
    fun addScore() {
        if (tries == 1) {
            score += 5;
        } else if (tries <= 4) {
            score += 3;
        } else {
            score += 1;
        }
    }
    fun updateTries() {
        val tryCounter = findViewById<TextView>(R.id.tryField);
        val string = "Próby: $tries";
        tryCounter.text = string;
    }
    fun retry(message: String, showInfo: Boolean = false) {
        rnd = ran.nextInt(20);
        val builder = AlertDialog.Builder(this@MainActivity)
        builder.setTitle(title)
        if (showInfo) {
            var info = "$message liczba prób: $tries"
            builder.setMessage(info);
        } else {
            builder.setMessage(message)
        }

        builder.setPositiveButton("OK"){ dialogInterface: DialogInterface, i: Int ->}

        val dialog: AlertDialog = builder.create()
        dialog.show()
        tries = 0;
        updateTries();
        updateScore();

        setRecord();
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getRecord();

        updateTries();
        val button  = findViewById<Button>(R.id.button);
        button.setOnClickListener {
            var guess: Int = Integer.parseInt(findViewById<EditText>(R.id.numberField).text.toString());
            if (tries > 10) {
                retry("Przegrałeś! Spróbuj ponownie...");
            }
            tries++;
            updateTries();
            if (guess > 20 || guess < 0) {
                toast("Podano nieprawidłową liczbę, spróbuj jeszcze raz...")
                tries = tries - 1;
            } else if (guess == rnd) {
                addScore();
                toast("Gratulacje!");
                retry("Wygrałeś!", true);
            } else if (guess > rnd) {
                toast("Twoja liczba jest większa");
            } else {
                toast("Twoja liczba jest mniejsza");
            }
        }
        val resetButton = findViewById<Button>(R.id.resetButton);
        resetButton.setOnClickListener {
            score = 0;
            retry("Zresetowano stan gry!");
        }
    }
}