/// <reference path="../_ref.d.ts" />

var sys_login = (user: UserModel): number => {
    UserManager.getInstance().setCurrentUser(user);

    return 0;
};
