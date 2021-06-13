#include <experimental/future>

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

int do_something(){

   std::cout << std::this_thread::get_id() << ": hello do_something. sleeping 0.1s\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   return 42;
}

void test_case1() {

   auto f = std::experimental::async_do( do_something )
            .then(
               []( auto fu ) {
                  std::cout << std::this_thread::get_id() << ": hello then1. sleeping 0.1s\n";
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
                  return 10. + fu.get();
               }
            )
            .then(
               []( auto fu ) {
                  std::cout << std::this_thread::get_id() << ": hello then2. sleeping 0.1s\n";
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
                  return "ans=" + std::to_string(fu.get());
               }
            );

   std::cout << std::this_thread::get_id() << ": " << f.get() << '\n';
}

void test_case2() {
   auto f = std::experimental::async_do( do_something );

   std::this_thread::sleep_for(std::chrono::milliseconds(200));

   auto f1 = std::move(f).then(
               []( auto fu ) {
                  std::cout << std::this_thread::get_id() << ": hello then1. sleeping 0.1s\n";
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
                  return 10. + fu.get();
               }
            );

   std::this_thread::sleep_for(std::chrono::milliseconds(200));

   auto f2 = std::move(f1).then(
               []( auto fu ) {
                  std::cout << std::this_thread::get_id() << ": hello then2. sleeping 0.1s\n";
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
                  return "ans=" + std::to_string(fu.get());
               }
            );

   std::cout << std::this_thread::get_id() << ": " << f2.get() << '\n';
}


int main() {
   std::cout << std::this_thread::get_id() << ": BEGIN MAIN\n";

   test_case1();
   test_case2();

   std::cout << std::this_thread::get_id() << ": END MAIN\n";
}
