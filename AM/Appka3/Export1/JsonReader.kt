package com.example.appka3

import android.util.JsonReader
import java.io.IOException
import java.io.InputStream
import java.io.InputStreamReader

// JSON USERLIST PARSER
@Throws(IOException::class)
fun readUserlistJsonStream(`in`: InputStream?): List<User>? {
    val reader = JsonReader(InputStreamReader(`in`, "UTF-8"))
    return try {
        readUsersArray(reader)
    } finally {
        reader.close()
    }
}
@Throws(IOException::class)
fun readUsersArray(reader: JsonReader): List<User>? {
    val list: MutableList<User> = ArrayList<User>()
    reader.beginArray()
    while (reader.hasNext()) {
        list.add(readUser(reader))
    }
    reader.endArray()
    return list
}
@Throws(IOException::class)
fun readUser(reader: JsonReader): User {
    var usr = User()
    reader.beginObject()
    while (reader.hasNext()) {
        val json_name = reader.nextName()
        when (json_name) {
            "id" -> {
                usr.id = reader.nextInt()
            } "name" -> {
                usr.name = reader.nextString()
            } "username" -> {
                usr.username = reader.nextString()
            } "email" -> {
                usr.email = reader.nextString()
            } "address" -> {
                readAddress(reader, usr.address)
            } "phone" -> {
                usr.phone = reader.nextString()
            } "website" -> {
                usr.website = reader.nextString()
            } "company" -> {
                readCompany(reader, usr.company)
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
    return usr
}
@Throws(IOException::class)
fun readAddress(reader: JsonReader, add: Address) {
    reader.beginObject()
    while (reader.hasNext()) {
        val name = reader.nextName()
        when (name) {
            "street" -> {
                add.street = reader.nextString()
            } "suite" -> {
                add.suite = reader.nextString()
            } "city" -> {
                add.city = reader.nextString()
            } "zipcode" -> {
                add.zipcode = reader.nextString()
            } "geo" -> {
                readGeo(reader, add.geo)
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
}
@Throws(IOException::class)
fun readGeo(reader: JsonReader, geo: Geo) {
    reader.beginObject()
    while (reader.hasNext()) {
        val name = reader.nextName()
        when (name) {
            "lat" -> {
                geo.lat = reader.nextDouble()
            } "lng" -> {
                geo.lng = reader.nextDouble()
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
}
fun readCompany(reader: JsonReader, comp: Company) {
    reader.beginObject()
    while (reader.hasNext()) {
        val json_name = reader.nextName()
        when (json_name) {
            "name" -> {
                comp.name = reader.nextString()
            } "catchPhrase" -> {
                comp.catchPhrase = reader.nextString()
            } "bs" -> {
                comp.bs = reader.nextString()
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
}
// ------------ READ TODOS -------------------
@Throws(IOException::class)
fun readTodolistJsonStream(`in`: InputStream?, userlist: List<User>) {
    val reader = JsonReader(InputStreamReader(`in`, "UTF-8"))
    return try {
        readTodolistArray(reader, userlist)
    } finally {
        reader.close()
    }
}
/* dodaje obiekt todo do listy Todo danego uzytkownika z listy  */
/* zgodnie z id uzytkownika i userid z todo                     */
fun addTodoForUser(todo: Todo, userlist: List<User>) {
    val user = userlist.find { it.id == todo.userId }
    user?.todoList?.add(todo)
}
@Throws(IOException::class)
fun readTodolistArray(reader: JsonReader, userlist: List<User>) {
    reader.beginArray()
    while (reader.hasNext()) {
        addTodoForUser(readTodo(reader), userlist)
    }
    reader.endArray()
}
@Throws(IOException::class)
fun readTodo(reader: JsonReader): Todo {
    var todo = Todo()
    reader.beginObject()
    while (reader.hasNext()) {
        val name = reader.nextName()
        when (name) {
            "userId" -> {
                todo.userId = reader.nextInt()
            } "id" -> {
                todo.id = reader.nextInt()
            } "title" -> {
                todo.title = reader.nextString()
            } "completed" -> {
                todo.completed = reader.nextBoolean()
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
    return todo
}
// ------------ READ POSTS -------------------
@Throws(IOException::class)
fun readPostJsonStream(`in`: InputStream?, userlist: List<User>) {
    val reader = JsonReader(InputStreamReader(`in`, "UTF-8"))
    return try {
        readPostArray(reader, userlist)
    } finally {
        reader.close()
    }
}
/* dodaje obiekt post do listy Posts danego uzytkownika z listy  */
/* zgodnie z id uzytkownika i userid z post */
fun addPostForUser(post: Post, userlist: List<User>) {
    val user = userlist.find { it.id == post.userId }
    user?.postList?.add(post)
}
@Throws(IOException::class)
fun readPostArray(reader: JsonReader, userlist: List<User>) {
    reader.beginArray()
    while (reader.hasNext()) {
        addPostForUser(readPost(reader), userlist)
    }
    reader.endArray()
}
@Throws(IOException::class)
fun readPost(reader: JsonReader): Post {
    var post = Post()
    reader.beginObject()
    while (reader.hasNext()) {
        val name = reader.nextName()
        when (name) {
            "userId" -> {
                post.userId = reader.nextInt()
            } "id" -> {
                post.id = reader.nextInt()
            } "title" -> {
                post.title = reader.nextString()
            } "body" -> {
                post.body = reader.nextString()
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
    return post
}
// ------------ READ COMMENTS -------------------
@Throws(IOException::class)
fun readCommentJsonStream(`in`: InputStream?): List<Comment>? {
    val reader = JsonReader(InputStreamReader(`in`, "UTF-8"))
    return try {
        readCommentArray(reader)
    } finally {
        reader.close()
    }
}
@Throws(IOException::class)
fun readCommentArray(reader: JsonReader): List<Comment>? {
    var list: ArrayList<Comment> = ArrayList()
    reader.beginArray()
    while (reader.hasNext()) {
        list.add(readComment(reader))
    }
    reader.endArray()
    return list
}
@Throws(IOException::class)
fun readComment(reader: JsonReader): Comment {
    var cmnt = Comment()
    reader.beginObject()
    while (reader.hasNext()) {
        val json_name = reader.nextName()
        when (json_name) {
            "postId" -> {
                cmnt.postId = reader.nextInt()
            } "id" -> {
                cmnt.id = reader.nextInt()
            } "name" -> {
                cmnt.name = reader.nextString()
            } "email" -> {
                cmnt.email = reader.nextString()
            } "body" -> {
                cmnt.body = reader.nextString()
            } else -> {
                reader.skipValue()
            }
        }
    }
    reader.endObject()
    return cmnt
}