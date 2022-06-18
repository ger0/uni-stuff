package com.example.appka3

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.TextView
import androidx.core.content.ContextCompat
import com.example.appka3.MainActivity.Companion.userList

class UserActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user)
        val idx = intent.getIntExtra("UserID", 0)
        if (userList != null) {
            val user = userList!![idx]
            val infoHeader: TextView = findViewById(R.id.userinfoHeader)
            infoHeader.text = user.username + "\n" + user.name

            val infoData: TextView = findViewById(R.id.userinfoData)
            infoData.text = user.details_str()

            val taskListview = findViewById<ListView>(R.id.taskListview)
            if (user.todoList != null) {
                val adapt =
                    ArrayAdapter(this, android.R.layout.simple_list_item_1, user.todoList)
                taskListview.adapter = adapt
            }

            val postListview = findViewById<ListView>(R.id.postListview)
            if (user.postList != null) {
                val adapt =
                    ArrayAdapter(this, android.R.layout.simple_list_item_1, user.postList)
                postListview.adapter = adapt
            }
            postListview.setOnItemClickListener { arg0, arg1, position, arg3 ->
                val intent = Intent(this, PostsActivity::class.java)
                intent.putExtra("PostID", user.postList[position].id)
                intent.putExtra("Title", user.postList[position].title)
                intent.putExtra("Body", user.postList[position].body)
                ContextCompat.startActivity(this, intent, Bundle.EMPTY)
            }
        }
    }
}