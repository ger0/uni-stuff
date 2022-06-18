package com.example.appka3

// Dane dotyczące użytkowników
class User(
    var id:         Int = -1,
    var name:       String = "",
    var username:   String = "",
    var email:      String = "",
    var address:    Address= Address(),
    var phone:      String = "",
    var website:    String = "",
    var company:    Company= Company()
) {
    override fun toString(): String {
        return "\n$username - $name\n $email \n\n" +
                "zad: " + todoList.size.toString() + ", " +
                "post: " + postList.size.toString()
    }
    fun details_str(): String {
        return email + "\n" + phone + "\n" + website + "\n" +
                address.str() + "\n" + company.str()
    }

    var todoList:   ArrayList<Todo> = ArrayList<Todo>()
    var postList:   ArrayList<Post> = ArrayList<Post>()
}
class Address(
    var zipcode:    String = "",
    var street:     String = "",
    var suite:      String = "",
    var city:       String = "",
    var geo:        Geo = Geo()
) {
    fun str(): String {
        return "$zipcode, $street, $suite\n $city, " + geo.str()
    }
}
class Geo(
    var lat:       Double = 0.0,
    var lng:       Double = 0.0
) {
    fun str(): String {
        return "lat: $lat, lng: $lng"
    }
}
class Company(
    var name:       String = "",
    var catchPhrase:String = "",
    var bs:         String = ""
){
    fun str(): String {
       return "$name\n $catchPhrase\n $bs"
    }
}