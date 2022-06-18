package com.example.appka3

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.TextView
import com.example.appka3.MainActivity.Companion.commentList

class PostsActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_posts)
        val postID = intent.getIntExtra("PostID", 0)

        val titleView: TextView = findViewById(R.id.titleView)
        titleView.text = intent.getStringExtra("Title")

        val bodyView: TextView = findViewById(R.id.bodyView)
        bodyView.text = intent.getStringExtra("Body")

        val commentListview = findViewById<ListView>(R.id.commentListview)
        if (commentList != null) {
            val adapt =
                ArrayAdapter(this, android.R.layout.simple_list_item_1,
                    commentList!!.filter { it.postId == postID}
                )
            commentListview.adapter = adapt
        }
    }
}