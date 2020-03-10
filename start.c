#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define PATH_SEPARATOR ';'   /*define it to be ':' on Solaris*/
#define USER_CLASSPATH "." /*where Prob.clss is*/

main() {
  JNIEnv *env = NULL;
  JavaVM* jvm = NULL;
  jint res;
  jclass cls;
  jclass local_clazz=NULL;
  jclass clazz = NULL;
  jmethodID mid;
  jstring jstr;
  jclass stringClass;
  jobjectArray args;
  JavaVMInitArgs vm_args;
  JavaVMOption options[1];
  options[0].optionString = "-Djava.class.path=" USER_CLASSPATH;
  vm_args.version = 0x00010002;
  vm_args.options = options;
  vm_args.nOptions =1;
  vm_args.ignoreUnrecognized = JNI_TRUE;
  /*create the java VM*/
  res = JNI_CreateJavaVM(&jvm, (void**)(&env), &vm_args);
  if (res < 0) {
    fprintf(stderr, "Can't create Java VM \n");
    exit(1);
  }
  cls = (*env)->FindClass(env, "Prog");
  if (cls == NULL) {
    goto destroy;
  }
  mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
  if (mid == NULL) {
    goto destroy;
  }
  jstr = (*env)->NewStringUTF(env, " from C!");
  if (jstr == NULL) {
    goto destroy;
  }
  stringClass = (*env)->FindClass(env, "java/lang/String");
  args = (*env)->NewObjectArray(env, 1, stringClass, jstr);
  if (args == NULL) {
    goto destroy;
  }
  printf("before NewGlobalRef\n");
  (*env)->NewGlobalRef(env, local_clazz);
  printf("after NewGlobalRef\n");
  printf("before goto detroy \n");
  goto destroy;
  printf("after goto destroy \n");
  (*env)->CallStaticVoidMethod(env, cls, mid, args);
  destroy:
    printf("enter destroy \n");
    assert(local_clazz == NULL);
    (*env)->DeleteLocalRef(env, local_clazz);
    printf("delete local ref NULL aready \n");
    (*env)->DeleteGlobalRef(env, clazz);
    printf("delete global ref NULL \n");
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
    }
    (*jvm)->DestroyJavaVM(jvm);
    printf("Hi OK\n");
}
