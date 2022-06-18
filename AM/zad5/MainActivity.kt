package com.example.appka3

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.os.AsyncTask
import android.os.Bundle
import android.view.View
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.ProgressBar
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat.startActivity
import java.io.InputStream
import java.lang.Thread.sleep
import java.net.URL


fun internetCheck(c: Context): Boolean {
    val cmg = c.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
    return cmg.activeNetworkInfo?.isConnectedOrConnecting == true
}
class MainActivity : AppCompatActivity() {
    companion object {
        var userList: List<User>? = null
        var commentList: List<Comment>? = null
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        findViewById<ProgressBar>(R.id.progressBar2)?.visibility = View.VISIBLE
        Thread() {
            run {
                while (internetCheck(this) == false) {
                    Thread.sleep(3000)
                    runOnUiThread(Runnable {Toast.makeText(this, "Brak połączenia z internetem...", Toast.LENGTH_SHORT).show()})
                }
            }
            runOnUiThread() {
                AsyncTaskLoad(this).execute()
            }
        }.start()
    }
    class AsyncTaskLoad(private var activity: MainActivity): AsyncTask<String, String, String>() {
        override fun onPreExecute() {
            super.onPreExecute()
        }
        override fun doInBackground(vararg p0: String?): String {
            // load userlist
            var url = "https://jsonplaceholder.typicode.com/users"
            println("TEST")
            var body = URL(url).readText()
            println("TEST")
            if (body != "") {
                var stream: InputStream = body.byteInputStream()
                userList = readUserlistJsonStream(stream)!!
            }
            // load todolist
            url = "https://jsonplaceholder.typicode.com/todos"
            body = URL(url).readText()
            if (body != "") {
                var stream: InputStream = body.byteInputStream()
                readTodolistJsonStream(stream, userList!!)
            }
            // load posts
            url = "https://jsonplaceholder.typicode.com/posts"
            body = URL(url).readText()
            if (body != "") {
                var stream: InputStream = body.byteInputStream()
                readPostJsonStream(stream, userList!!)
            }
            // load comments
            url = "https://jsonplaceholder.typicode.com/comments"
            body = URL(url).readText()
            if (body != "") {
                var stream: InputStream = body.byteInputStream()
                commentList = readCommentJsonStream(stream)
            }
            return "ok"
        }
        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)
            activity?.findViewById<ProgressBar>(R.id.progressBar2)?.visibility = View.INVISIBLE
            val listView = activity?.findViewById<ListView>(R.id.taskListview)
            if (userList != null) {
                val adapt =
                    ArrayAdapter<User>(activity, android.R.layout.simple_list_item_1, userList!!)
                listView.adapter = adapt
            }
            listView.setOnItemClickListener { arg0, arg1, position, arg3 ->
                val intent = Intent(activity, UserActivity::class.java)
                intent.putExtra("UserID", position)
                startActivity(activity, intent, Bundle.EMPTY)
            }
        }
    }
}