const db=require('../database.js');
const bcrypt=require('bcryptjs');


const user={

	getAllUsers(callback){
		return db.query('SELECT * FROM user',callback);
	},
	
	getOneUser(username,callback){
		return db.query('SELECT * FROM user WHERE username=?',
		[username], callback);
	},
		
	addUser(newData, callback) {
		bcrypt.hash(newData.password,10,function(err,hashedPassword){
			return db.query('INSERT INTO user (username, fname, lname, email, phone_no, address, password) VALUES(?,?,?,?,?,?,?)',
			[newData.username, newData.fname, newData.lname, newData.email, newData.phone_no, newData.address, hashedPassword],callback);	
		});
	},
	
	updateUser(updateData, username, callback) {
		bcrypt.hash(updateData.password,10,function(err,hashedPassword){
			return db.query('UPDATE user SET fname=?, lname=?, email=?, phone_no=?, address=?, password=? WHERE username=?',
			[updateData.fname, updateData.lname, updateData.email, updateData.phone_no, updateData.address, hashedPassword, username],callback);
		});
	},
	/* VANHA METODI
	updateFname(updateData, username, callback) {
		return db.query('UPDATE user SET fname=? WHERE username=?',[updateData.fname, username],callback);
	},

	updateLname(updateData, username, callback) {
		return db.query('UPDATE user SET lname=? WHERE username=?',[updateData.lname, username],callback);
	},

	updateEmail(updateData, username, callback) {
		return db.query('UPDATE user SET email=? WHERE username=?',[updateData.email, username],callback);
	},

	updatePhone_no(updateData, username, callback) {
		return db.query('UPDATE user SET phone_no=? WHERE username=?',[updateData.phone_no, username],callback);
	},

	updateAddress(updateData, username, callback) {
		return db.query('UPDATE user SET address=? WHERE username=?',[updateData.address, username],callback);
	},

	updatePassword(updateData, username, callback) {
		bcrypt.hash(updateData.password,10,function(err,hashedPassword){
			return db.query('UPDATE user SET password=? WHERE username=?',[hashedPassword, username],callback);
		});
	},
	*/
	deleteUser(username,callback){
		return db.query('DELETE FROM user WHERE username=?',[username], callback)
	},

	login(username,callback){
		return db.query('SELECT password FROM user WHERE username=?',[username], callback);
	},

	updateUserDetails(updateData, username, callback) {

		if (updateData.fname) {
			return db.query('UPDATE user SET fname=? WHERE username=?',
			[updateData.fname, username], callback);
		}
		
		else if (updateData.lname) {
			return db.query('UPDATE user SET lname=? WHERE username=?',
			[updateData.lname, username], callback);
		}
		
		else if (updateData.email) {
			return db.query('UPDATE user SET email=? WHERE username=?',
			[updateData.email, username], callback);
		}
		
		else if (updateData.phone_no) {
			return db.query('UPDATE user SET phone_no=? WHERE username=?',
			[updateData.phone_no, username], callback);
		}
		
		else if (updateData.address) {
			return db.query('UPDATE user SET address=? WHERE username=?',
			[updateData.address, username], callback);
		}
		
		else if (updateData.password) {
			bcrypt.hash(updateData.password,10,function(err,hashedPassword){
				return db.query('UPDATE user SET password=? WHERE username=?',
				[hashedPassword, username], callback);
			});
		}
	}

}

module.exports=user;